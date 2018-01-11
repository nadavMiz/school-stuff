#include <sys/inotify.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>

#include "fileDiscoverer.h"
#include "queue.h"

#define TRUE 1
#define MASK_SIZE 8 
#define FILE_DETECTOR_SLEEP 3
#define EVENT_SIZE (sizeof(struct inotify_event) + PATH_SIZE + 1)

typedef struct
{
	pthread_mutex_t m_flagMutex;
	ZLog m_log;
	char m_inputPath[PATH_SIZE];
	char m_outputPath[PATH_SIZE];
	char m_invalidPath[PATH_SIZE];
	char m_mask[MASK_SIZE];
	Queue* m_outputQueue;
	int m_isEnd;
	int m_isPause;
} Context;

struct Discoverer
{
	Context* m_context;
	pthread_t m_thread;
};


/*-----------------------------------------------*/

static int IsEnd(Context* _context)
{
	int result;
	
	pthread_mutex_lock(&(_context->m_flagMutex));
	result = _context->m_isEnd;
	pthread_mutex_unlock(&(_context->m_flagMutex));
	
	return result;
}

/*-----------------------------------------------*/

static int IsPause(Context* _context)
{
	int result;
	
	pthread_mutex_lock(&(_context->m_flagMutex));
	result = _context->m_isPause;
	pthread_mutex_unlock(&(_context->m_flagMutex));
	
	return result;
}

/*-----------------------------------------------*/

static Context* CreateContext(Queue* _output, char* _inputPath, char* _outputPath,
										char* _invalidPath , char* _mask ,ZLog _log)
{
	Context* context = malloc(sizeof(Context));
	if(NULL == context)
	{
		return NULL;
	}
	if(pthread_mutex_init(&(context->m_flagMutex), NULL) < 0)
	{
		free(context);
		return NULL;
	}
	context->m_outputQueue = _output;
	context->m_log = _log;
	strcpy(context->m_inputPath, _inputPath);
	strcpy(context->m_outputPath, _outputPath);
	strcpy(context->m_mask, _mask);
	strcpy(context->m_invalidPath, _invalidPath);
	context->m_isEnd = 0;
	context->m_isPause = 0;
	
	
	return context;
}

/*-----------------------------------------------*/

static void DestroyContext(Context* _context)
{
	pthread_mutex_destroy(&(_context->m_flagMutex));
	free(_context);
}

/*-----------------------------------------------*/

static Discoverer* CreateDiscovererStruct(Queue* _output, char* _inputPath, char* _outputPath,
										char* _invalidPath , char* _mask ,ZLog _log)
{
	Discoverer* thread = malloc(sizeof(Discoverer));
	if(NULL == thread)
	{
		return NULL;
	}
	
	thread->m_context = CreateContext(_output, _inputPath, _outputPath, _invalidPath, _mask, _log);
	if(NULL == thread->m_context)
	{
		free(thread);
		return NULL;
	}
	
	return thread;
}

/*-----------------------------------------*/

static void DestroyDiscoverer(Discoverer* _discoverer)
{
	DestroyContext(_discoverer->m_context);
	free(_discoverer);
}

/*-----------------------------------------*/

static void CombineAdressToDest(char* _fileName, const char* _path, char* _dest)
{	
	strcpy(_dest, _path);
	strcat(_dest, "/");
	strcat(_dest, _fileName);
}

/*------------------------------------*/

static void* ExitThread(DIR* _directory)
{
	closedir(_directory);
	pthread_exit(NULL);
}

/*------------------------------------*/

void TransferFile(char* _inputFileName, Context* _context, char* _outputPath)
{
	char outPath[PATH_SIZE];
	char inPath[PATH_SIZE];
	
	CombineAdressToDest(_inputFileName, _outputPath, outPath);
	CombineAdressToDest(_inputFileName, _context->m_inputPath, inPath);
	
	if(rename(inPath, outPath) < 0)
	{
		ZLOG(_context->m_log, LOG_CRITICAL, "can't transfer file");
	}
}

/*------------------------------------*/

int IsFileExtensionOK(char* _fileName, char* _mask)
{
	char* extension;
	
	extension = _fileName + (strlen(_fileName) - strlen(_mask));
	return (NULL != extension && (0 == strcmp(extension, _mask)));
}

/*------------------------------------*/

void SendFileForParsing(Context* _context, char* _fileName)
{
	char* outPath = malloc(sizeof(char) * PATH_SIZE);
	
	CombineAdressToDest(_fileName, _context->m_outputPath, outPath);
	
	if(QueueInsert(_context->m_outputQueue, outPath) != ERR_OK)
	{
		ZLOG(_context->m_log, LOG_CRITICAL, "problem sending file")
		return;
	}
	ZLOG(_context->m_log, LOG_TRACE, "sent file name for processing")	
}

/*------------------------------------*/

static void HandleIncomingFile(Context* _context, struct dirent* _dp)
{
	
	if(!IsFileExtensionOK(_dp->d_name, _context->m_mask))
	{
		ZLOG(_context->m_log, LOG_WARNING, "invalid file extension for file: %s", _dp->d_name)
		
		TransferFile(_dp->d_name, _context, _context->m_invalidPath);
		return;
	}
	
	TransferFile(_dp->d_name, _context, _context->m_outputPath);
	
	SendFileForParsing(_context, _dp->d_name);
}

/*------------------------------------*/

void* FileDiscoverer(Context* _context)
{
	DIR* directory;
	struct dirent* dp;
	
	directory = opendir(_context->m_inputPath);
	if(NULL == directory)
	{
		ZLOG(_context->m_log ,LOG_CRITICAL, "couldn't open input directory")
		pthread_exit(NULL);
	}
	
	while(!IsEnd(_context))
	{	
		/* send all files in  */
		while ((dp = readdir(directory)) != NULL)
		{
			/*ignore the parent directory and the directory itself*/
			if((0 == strcmp(dp->d_name, ".")) || (0 == strcmp(dp->d_name, "..")))
			{
				continue;
			}
			
			HandleIncomingFile(_context, dp);
		}
		
		sleep(FILE_DETECTOR_SLEEP);
		
		rewinddir(directory);
		
		while(IsPause(_context))
		{
			pause();
		}
	}
	
	return ExitThread(directory);
}
	
/*-------------------------------------------------------------------------*/

Discoverer* CreateFileDiscovererThread(Queue* _output, char* _inputPath, char* _outputPath,
										char* _invalidPath , char* _mask ,ZLog _log)
{
	Discoverer* discoverer;
	
	discoverer = CreateDiscovererStruct(_output, _inputPath, _outputPath, _invalidPath, _mask, _log);
	if(NULL == discoverer)
	{
		ZLOG(_log, LOG_SEVERE, "allocation failed: can't creat file discoverer")
		return 0;
	}
	
	if(0 != pthread_create(&(discoverer->m_thread), NULL, (void * (*)(void *))FileDiscoverer, discoverer->m_context))
	{
		perror("thread create");
	}
	
	return discoverer;
}

/*----------------------------------------------------------*/

int JoinFileDiscoverer(Discoverer* _discoverer)
{
	int status;
	
	status = pthread_join(_discoverer->m_thread ,NULL);
	DestroyDiscoverer(_discoverer);
	
	return status;
}

/*----------------------------------------------------------*/

void PauseFileDiscoverer(Discoverer* _discoverer)
{
	pthread_mutex_lock(&(_discoverer->m_context->m_flagMutex));
	_discoverer->m_context->m_isPause = 1;
	pthread_mutex_unlock(&(_discoverer->m_context->m_flagMutex));
}

/*----------------------------------------------------------*/

void ResumeFileDiscoverer(Discoverer* _discoverer, int _signal)
{
	pthread_mutex_lock(&(_discoverer->m_context->m_flagMutex));
	_discoverer->m_context->m_isPause = 0;
	pthread_mutex_unlock(&(_discoverer->m_context->m_flagMutex));
	
	pthread_kill(_discoverer->m_thread, _signal);
}


/*----------------------------------------------------------*/

void CloseFileDiscoverer(Discoverer* _discoverer, int _signal)
{
	pthread_mutex_lock(&(_discoverer->m_context->m_flagMutex));
	_discoverer->m_context->m_isPause = 0;
	_discoverer->m_context->m_isEnd = 1;
	pthread_mutex_unlock(&(_discoverer->m_context->m_flagMutex));
	
	pthread_kill(_discoverer->m_thread, _signal);
}
