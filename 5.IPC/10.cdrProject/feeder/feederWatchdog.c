#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

#include "feederWatchdog.h"
#include "CDRparser.h"
#include "fileDiscoverer.h"
#include "controller.h"

#define TRUE 1

typedef struct
{
	Channel m_uiInChannel;
	Channel m_uiOutChannel;
	ParserThreads* m_parsers;
	Discoverer* m_discoverer;
	
} WatchDogContext;

struct WachDogThread
{
	pthread_t m_thread;
	WatchDogContext* m_context;
};

/*------------------------------*/

void VoidSignal(int _sig)
{
	
}

/*-------------------------------*/

void InitializeVoidSignal()
{
	struct sigaction sa;
	sa.sa_handler = VoidSignal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) 
    {
        perror("sigaction");
        exit(1);
    }
}

/*---------------------------------*/

static WatchDogContext* CreateContext(Channel _uiInChannel, Channel _uiOutChannel,
								 ParserThreads* _parsers, Discoverer* _discoverer)
{
	WatchDogContext* context = malloc(sizeof(WatchDogContext));
	if(NULL == context)
	{
		return NULL;
	}
	
	context->m_uiInChannel = _uiInChannel;
	context->m_uiOutChannel = _uiOutChannel;
	context->m_parsers = _parsers;
	context->m_discoverer = _discoverer;
	
	return context;
}

/*---------------------------------*/

static void DestroyContext(WatchDogContext* _context)
{
	free(_context);
}

/*---------------------------------*/

static WachDogThread* CreateWachDogThread(Channel _uiInChannel, Channel _uiOutChannel,
										 ParserThreads* _parsers, Discoverer* _discoverer)
{
	WachDogThread* thread = malloc(sizeof(WachDogThread));
	if(NULL == thread)
	{
		return NULL;
	}
	
	thread->m_context = CreateContext(_uiInChannel, _uiOutChannel, _parsers, _discoverer);
	if(NULL == thread->m_context)
	{
		free(thread);
		return NULL;
	}
	
	return thread;
}

/*---------------------------------*/

static void DestroyWachDogThread(WachDogThread* _watchDog)
{
	DestroyContext(_watchDog->m_context);
	free(_watchDog);
}

/*----------------------------------*/

static void TerminateProcess(WatchDogContext* _context)
{
	CloseFileDiscoverer(_context->m_discoverer, SIGUSR1);
	CloseParseThreads(_context->m_parsers, SIGUSR1);
}

/*----------------------------------*/

static void PauseProcess(WatchDogContext* _context)
{
	PauseFileDiscoverer(_context->m_discoverer);
	PauseParseThreads(_context->m_parsers);
}

/*----------------------------------*/

static void ResumeProcess(WatchDogContext* _context)
{
	ResumeFileDiscoverer(_context->m_discoverer, SIGUSR1);
	ResumeParseThreads(_context->m_parsers, SIGUSR1);
}

/*----------------------------------*/

void* WatchDogFunc(WatchDogContext* _context)
{
	int uiMsg;
	
	InitializeVoidSignal();
	
	while(TRUE)
	{
		if(msgRecive(_context->m_uiInChannel, sizeof(int), &uiMsg) < 0)
		{
			continue;
		}
		
		switch(uiMsg)
		{
			case PAUSE:
				PauseProcess(_context);
				break;
				
			case RESUME:
				ResumeProcess(_context);
				break;
				
			case SHUT_DOWN:
				TerminateProcess(_context);
				MsgSend(_context->m_uiOutChannel, sizeof(int), &uiMsg);
				pthread_exit(NULL);
				break;

		}
	}
}

/*--------------------------------*/

WachDogThread* CreateWatchdog(Channel _uiInChannel, Channel _uiOutChannel,
							 ParserThreads* _parsers, Discoverer* _discoverer)
{
	WachDogThread* watchDog;
	
	watchDog = CreateWachDogThread(_uiInChannel, _uiOutChannel, _parsers, _discoverer);
	 
	if(0 != pthread_create(&(watchDog->m_thread), NULL, (void * (*)(void *))WatchDogFunc, watchDog->m_context))
	{
		perror("thread create");
	}
	
	return watchDog;
}

/*---------------------------------*/

void JoinWatchDog(WachDogThread* _watchdog)
{
	if(pthread_join(_watchdog->m_thread ,NULL) != 0)
	{
		fprintf(stderr, "thread join failed\n");
	}
	
	DestroyWachDogThread(_watchdog);
}

/*-----------------------------------*/
