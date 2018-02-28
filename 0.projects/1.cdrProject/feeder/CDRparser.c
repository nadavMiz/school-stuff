#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

#include "zlog4c.h"
#include "CDRparser.h"
#include "communication.h"
#include "fileDiscoverer.h"
#include "queue.h"

#define TRUE 1
#define NUM_CDR_ELEMENTS 13
#define CALL_TYPE_LENGH 8
#define NUM_CALL_TYPES 5
#define NUM_THREADS 3
#define CDR_FORMAT "%15[^|]|%15[^|]|%15[^|]|%64[^|]|%d|%7[^|]|%10[^|]|%10[^|]|%u|%f|%f|%15[^|]|%d"

typedef struct
{
	pthread_mutex_t m_flagMutex;
	ZLog m_log;
	char m_outputPath[PATH_SIZE];
	Queue* m_inQueue;
	Channel m_outChannel;
	int m_isEnd;
	int m_isPause;
} Context;

struct ParserThreads
{
	pthread_t* m_threads;
	Context* m_context;
	size_t m_size;
};

/*-----------------------------------------------------*/

static int IsEnd(Context* _context)
{
	int result;
	
	pthread_mutex_lock(&(_context->m_flagMutex));
	result = _context->m_isEnd;
	pthread_mutex_unlock(&(_context->m_flagMutex));
	
	return result;
}

/*-----------------------------------------------------*/

static int IsPause(Context* _context)
{
	int result;
	
	pthread_mutex_lock(&(_context->m_flagMutex));
	result = _context->m_isPause;
	pthread_mutex_unlock(&(_context->m_flagMutex));
	
	return result;
}

/*-------------------------------------------------------*/

int TakeLine(FILE* _stream, char* _line)
{
	if(fgets(_line, LINE_LENGTH, _stream) == NULL)
	{
		return 0;
	}
	return 1;
}

/*--------------------------------------------------------*/

static int convertCallTypeStr(char* _callType)
{
	static char table[][7] = {"MOC", "MTC", "SMS-MO", "SMS-MT", "GPRS"};
	int callTypeNum;
	
	for(callTypeNum = 0; callTypeNum < NUM_CALL_TYPES; ++callTypeNum)
	{
		if(0 == strcmp(_callType, table[callTypeNum]))
		{
			return callTypeNum;
		}
	}
	return -1;
}

int parseCdr(char* _cdr, CDRdata* _data, ZLog _log)
{
	/*TODO change so it will accept blank fields*/
	char callType[CALL_TYPE_LENGH];
	
	sscanf(_cdr, CDR_FORMAT, _data->m_imsi, _data->m_msisdn,
	    _data->m_imei, _data->m_operatorBrand, &(_data->m_operatorNumber),
	    callType, _data->m_callDate, _data->m_callTime,
	    &(_data->m_duration), &(_data->m_download),
		&(_data->m_upload), _data->m_partyMSISDN, &(_data->m_partyOperator));
	
	_data->m_calltype = convertCallTypeStr(callType);
	if(-1 == _data->m_calltype)
	{
		ZLOG(_log, LOG_CRITICAL,"cdrParser: unnown call type:%s", callType);
		return 0;
	}
	
	return 1;
}

/*---------------------------------------------*/

static void* ExitThread(Context* _context)
{
	pthread_exit(NULL);
}

/*---------------------------------------------*/

void ReadFile(Context* _context, char* _fileName)
{
	char cdr[LINE_LENGTH];
	int count;
	CDRdata data;
	FILE* file;
	
	file = fopen(_fileName, "r");
	if(NULL == file)
	{
		ZLOG(_context->m_log, LOG_CRITICAL, "can't open cdr file");
		return;
	}

	/*take header line*/
	TakeLine(file, cdr);
	/*parse file*/
	while(0 != TakeLine(file, cdr))
	{
		++count;
		if(parseCdr(cdr, &data, _context->m_log) == 0)
		{
			ZLOG(_context->m_log, LOG_ERROR, "invalid cdr data");
			continue;
		}
	
		if(MsgSend(_context->m_outChannel, sizeof(CDRdata), &data) < 0)
		{
			ZLOG(_context->m_log, LOG_ERROR, "msg send error #%d", errno);
		}
		else
		{
			ZLOG(_context->m_log, LOG_TRACE, "sent cdr to processor");
		}
		
		/*pause or exit shut down if needed*/
		while(IsPause(_context))
		{
			pause();
		}
		
		if(IsEnd(_context))
		{
			fclose(file);
			ExitThread(_context);
		}
	}

	if(fclose(file) < 0)
	{
		ZLOG(_context->m_log, LOG_CRITICAL, "cant close file");
	}
}

/*---------------------------------------------*/

void* ParseThread(Context* _context)
{
	char* inputFileName; 
	while(!IsEnd(_context))
	{
		/*recive msg*/
		if(QueueRemove(_context->m_inQueue, (void**)&inputFileName) != ERR_OK)
		{
			ZLOG(_context->m_log, LOG_CRITICAL, "queue remove failed")
			break;
		}
		ZLOG(_context->m_log, LOG_TRACE, "file recived. file name: %s", inputFileName);
		
		ReadFile(_context, inputFileName);
		
		free(inputFileName);
	}
	return ExitThread(_context);
}

/*---------------------------------------------------------------*/

static Context* CreateContext(Queue* _input, Channel _output, char* _outputPath, ZLog _log)
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
	/*fill context data*/
	strcpy(context->m_outputPath, _outputPath);
	context->m_inQueue = _input;
	context->m_outChannel = _output;
	context->m_log = _log;
	context->m_isEnd = 0;
	context->m_isPause = 0;
	return context;
}

/*----------------------------------------------------------------*/

static void DestroyContext(Context* _context)
{
	pthread_mutex_destroy(&(_context->m_flagMutex));
	free(_context);
}

/*----------------------------------------------------------------*/

static ParserThreads* CreateParserThreads(size_t _size, Queue* _input, Channel _output, char* _outputPath, ZLog _log)
{
	ParserThreads* threads = malloc(sizeof(ParserThreads));
	if(NULL == threads)
	{
		return NULL;
	}
	
	threads->m_context = CreateContext(_input, _output, _outputPath, _log);
	if(NULL == threads->m_context)
	{
		free(threads);
		return NULL;
	}
	
	threads->m_threads = malloc(_size * sizeof(pthread_t));
	if(NULL == threads->m_threads)
	{
		DestroyContext(threads->m_context);
		free(threads);
		return NULL;
	}
	
	threads->m_size = _size;
	
	return threads;
}

/*--------------------------------------------------------------*/

void DestroyParserThreads(ParserThreads* threadStruct)
{
	free(threadStruct->m_threads);
	DestroyContext(threadStruct->m_context);
	free(threadStruct);
}

/*--------------------------------------------------------------*/

ParserThreads* CreateParseThreads(Queue* _input, Channel _output, char* _outputPath, ZLog _log)
{
	ParserThreads* threads;
	size_t i;
	
	threads = CreateParserThreads(NUM_THREADS, _input, _output, _outputPath, _log);
	if(NULL == threads)
	{
		return NULL;
	}
	
	/*create threads*/
	for(i = 0; i < NUM_THREADS; ++i)
	{
		if(0 != pthread_create(&(threads->m_threads[i]), NULL, (void * (*)(void *))ParseThread, threads->m_context))
		{
			perror("thread create");
		}
	}
	
	return threads;
}

/*-----------------------------------------------------*/

int JoinParseThreads(ParserThreads* _threads)
{
	size_t i;
	int status;
	
	for(i = 0; i < _threads->m_size; ++i)
	{
		status = pthread_join(_threads->m_threads[i] ,NULL);
		if(status != 0)
		{
			fprintf(stderr, "%d thread join failed\n", status);
		}
	}
	DestroyParserThreads(_threads);
	return 1;
}

/*---------------------------------------------------------*/

void PauseParseThreads(ParserThreads* _threads)
{
	pthread_mutex_lock(&(_threads->m_context->m_flagMutex));
	_threads->m_context->m_isPause = 1;
	pthread_mutex_unlock(&(_threads->m_context->m_flagMutex));
}

/*----------------------------------------------------------*/

void ResumeParseThreads(ParserThreads* _threads, int _signal)
{
	size_t i;
	
	pthread_mutex_lock(&(_threads->m_context->m_flagMutex));
	_threads->m_context->m_isPause = 0;
	pthread_mutex_unlock(&(_threads->m_context->m_flagMutex));
	
	for(i = 0; i < _threads->m_size; ++i)
	{
		pthread_kill(_threads->m_threads[i], _signal);
	}
}

/*--------------------------------------------------------*/

void CloseParseThreads(ParserThreads* _threads, int _signal)
{
	size_t i;
	
	pthread_mutex_lock(&(_threads->m_context->m_flagMutex));
	_threads->m_context->m_isEnd = 1;
	_threads->m_context->m_isPause = 0;
	pthread_mutex_unlock(&(_threads->m_context->m_flagMutex));
	
	for(i = 0; i < _threads->m_size; ++i)
	{
		pthread_kill(_threads->m_threads[i], _signal);
	}
}

