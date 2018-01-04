#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <sys/syscall.h>

#include "processorConfigParser.h"
#include "Recievers.h"
#include "retriver.h"
#include "operator.h"
#include "subscriber.h"
#include "communication.h"
#include "CDRparser.h"
#include "zlog4c.h"
#include "CGF.h"
#include "controller.h"

#define NUM_UI_LISTENERS 1
#define NUM_SUBSCRIBERS 100000
#define NUM_OPERATORS 100000
#define PATH_LENGTH 128
#define TRUE 1
#define MODULE_NAME "#"
#define LOG_CONFIG_PATH "../config/processorConf"

struct Recievers
{
	pthread_t* m_threads;
	size_t m_numThreads;
};

struct RecieverData
{
	pthread_mutex_t m_flagMutex;
	char m_outputPath[PATH_LENGTH];
	ZLog m_log;
	Retriver* m_subscribers;
	Retriver* m_operators;
	Channel m_uiInChannel;
	Channel m_uiOutChannel;
	Channel m_uiFeederInChannel;
	Channel m_uiFeederOutChannel;
	Channel m_feederChannel;
	size_t m_numCdrReaders;
	int m_isEnd;
	int m_isPause;
};

typedef struct 
{
	RecieverData* m_data;
	Recievers* m_cdrReaders; 
	
} UiReaderContext;

/*-----------------------------------*/

void VoidDestroyer(void* _dummy)
{
	return;
}

/*--------------------------------*/

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

/*-----------------------------------*/

UiReaderContext* CreateUiReaderContext(RecieverData* _data, Recievers* _cdrReaders)
{
	UiReaderContext* context = malloc(sizeof(UiReaderContext));
	if(NULL == context)
	{
		return NULL;
	}
	
	context->m_data = _data;
	context->m_cdrReaders = _cdrReaders;
	
	return context;
}

/*-----------------------------------*/

RecieverData* CDRreciverInit(ProcessorConfigue* _config)
{
	RecieverData* data = malloc(sizeof(RecieverData));
	if(NULL == data)
	{
		return NULL;
	}
	
	data->m_subscribers = RetriverCreate(NUM_SUBSCRIBERS, (size_t(*)(const void*))SubscriberHash,
										 (int(*)(const void*, const void*))SubscriberMatch);
	if(NULL == data->m_subscribers)
	{
		free(data);
		return NULL;
	}
	
	data->m_operators = RetriverCreate(NUM_OPERATORS, (size_t(*)(const void*))OperatorHash,
										 (int(*)(const void*, const void*))OperatorMatch);
										 
	if(NULL == data->m_operators)
	{
		RetriverDestroy(&(data->m_subscribers), VoidDestroyer);
		free(data);
		return NULL;
	}
	
	if(pthread_mutex_init(&(data->m_flagMutex), NULL) < 0)
	{
		RetriverDestroy(&(data->m_subscribers), VoidDestroyer);
		RetriverDestroy(&(data->m_operators), VoidDestroyer);
		free(data);
		return NULL;
	}
	
	data->m_log =  ZLogGet(MODULE_NAME, LOG_CONFIG_PATH);
	if(NULL == data->m_log)
	{
		RetriverDestroy(&(data->m_operators), VoidDestroyer);
		RetriverDestroy(&(data->m_subscribers), VoidDestroyer);
		pthread_mutex_destroy(&(data->m_flagMutex));
		free(data);
	}
	
	data->m_numCdrReaders = _config->m_numThreads;
	strcpy(data->m_outputPath, _config->m_reportPath);
	data->m_feederChannel = CreateChannel(CDR_MOVER_CHANNEL);
	data->m_uiInChannel = CreateChannel(UI_TO_PROCESSOR_CHANNEL);
	data->m_uiOutChannel = CreateChannel(UI_FROM_PROCESSOR_CHANNEL);
	data->m_uiFeederInChannel = CreateChannel(FEEDER_TO_PROCESSOR);
	data->m_uiFeederOutChannel = CreateChannel(PROCESSOR_TO_FEEDER);
	data->m_isEnd = 0;
	data->m_isPause = 0;
	
	return data;
}

/*----------------------------------------*/

static Recievers* CreateRecievers(size_t _size)
{
	Recievers* recievers;
	
	recievers = malloc(sizeof(Recievers));
	if(NULL == recievers)
	{
		return NULL;
	}
	
	recievers->m_numThreads = _size;
	recievers->m_threads = malloc(_size * sizeof(pthread_t));
	if(NULL == recievers->m_threads)
	{
		free(recievers);
		return NULL;
	}
	
	return recievers;
}

/*----------------------------------------*/

static void DestroyRecievers(Recievers* _Recievers)
{
	free(_Recievers->m_threads);
	free(_Recievers);
}

/*----------------------------------------*/

void SubscriberAddDataWrapper(const char* _key, Subscriber* _subscriber, CDRdata* _data)
{
	SubscriberAddData(_subscriber, _data);
}

static void InsertSubscriberData(RecieverData* _data, CDRdata* _inputData)
{
	char* subscriberKey;
	Subscriber* subscriber;
	
	/*get the subscribers key*/
	subscriberKey = GetSubscriberKey(_inputData);
	if(NULL == subscriberKey)
	{
		ZLOG(_data->m_log, LOG_SEVERE, "allocation error")
	}
	
	/*check if subscriber already exist*/
	/*if subscriber doesnt exist*/
	subscriber = CreateSubscriber();
	if(NULL == subscriber)
	{
		ZLOG(_data->m_log, LOG_SEVERE, "allocation error")
		return;
	}
	
	if(RETRIVER_SUCCESS == RetriverMerge(_data->m_subscribers, subscriberKey
										,subscriber, (ActionFunction)SubscriberAddDataWrapper, _inputData))
	{
		ZLOG(_data->m_log, LOG_TRACE, "added new subscriber")
	}
	else
	{
		DestroySubscriber(subscriber);
		DestroySubscriberKey(subscriberKey);
	}
		
	/*update subscribers data*/
	RetriverActionByKey(_data->m_subscribers, subscriberKey, (ActionFunction)SubscriberAddDataWrapper, _inputData);
	ZLOG(_data->m_log, LOG_TRACE, "updated subscriber")
	
}

/*-----------------------------------------------------------*/

void OperatorAddDataWrapper(const char* _key, Operator* _operator, CDRdata* _data)
{
	OperatorAddData(_operator, _data);
}

static void InsertOperatorData(RecieverData* _data, CDRdata* _inputData)
{
	int* operatorKey;
	Operator* operator;
	
	/*get the subscribers key*/
	operatorKey = GetOperatorKey(_inputData);
	if(NULL == operatorKey)
	{
		ZLOG(_data->m_log, LOG_SEVERE, "allocation error")
	}
	
	/*check if subscriber already exist*/
	/*if subscriber doesnt exist*/
	operator = CreateOperator();
	if(NULL == operator)
	{
		ZLOG(_data->m_log, LOG_SEVERE, "allocation error")
	}
	
	if(RETRIVER_SUCCESS == RetriverMerge(_data->m_operators, operatorKey
										,operator, (ActionFunction)OperatorAddDataWrapper, _inputData))
	{
		ZLOG(_data->m_log, LOG_TRACE, "added new operator")
	}
	else
	{
		DestroyOperator(operator);
		DestroyOperatorKey(operatorKey);
	}
		
	/*update operators data*/
	ZLOG(_data->m_log, LOG_TRACE, "updated operator")
	
}

/*-----------------------------------------------------*/

static int IsEnd(RecieverData* _data)
{
	int result;

	pthread_mutex_lock(&(_data->m_flagMutex));
	result = _data->m_isEnd;
	pthread_mutex_unlock(&(_data->m_flagMutex));
	
	return result;
}

/*-----------------------------------------------------*/

static int IsPause(RecieverData* _data)
{
	int result;

	pthread_mutex_lock(&(_data->m_flagMutex));
	result = _data->m_isPause;
	pthread_mutex_unlock(&(_data->m_flagMutex));
	
	return result;
}

/*-----------------------------------------------------*/

static void msgReciveErrorHandle(ZLog _log)
{
	if(EINTR == errno)
	{
		ZLOG(_log, LOG_CRITICAL, "msg recive was intrupted")
	}
	else
	{
		ZLOG(_log, LOG_CRITICAL, "msg recive failed error #%d", errno)
	}
}

/*-----------------------------------------------------*/

void* CDRreader(RecieverData* _data)
{
	CDRdata inputData;
	
	while(!IsEnd(_data))
	{
		if(msgRecive(_data->m_feederChannel, sizeof(CDRdata), &inputData) < 0)
		{
			msgReciveErrorHandle(_data->m_log);
			continue;
		}
		ZLOG(_data->m_log, LOG_TRACE, "got new msg")
		
		InsertSubscriberData(_data, &inputData);

		InsertOperatorData(_data, &inputData);
		
		while(IsPause(_data))
		{
			pause();
		}
	}
	pthread_exit(NULL);
}

Recievers* CreateCdrReadingThreads(RecieverData* _data)
{
	size_t i;
	Recievers* threads;
	
	threads = CreateRecievers(_data->m_numCdrReaders);
	if(NULL == threads)
	{
		return NULL;
	}
	
	for(i = 0; i < _data->m_numCdrReaders; ++i)
	{
		if(0 != pthread_create(&(threads->m_threads[i]), NULL, (void * (*)(void *))CDRreader, _data))
		{
			perror("thread create");
		}
	}
	
	return threads;
}

/*----------------------------------------------------*/

static void CloseCdrReaders(RecieverData* _data, Recievers* _cdrReaderd)
{
	size_t i;
	
	pthread_mutex_lock(&(_data->m_flagMutex));
	_data->m_isEnd = 1;
	_data->m_isPause = 0;
	pthread_mutex_unlock(&(_data->m_flagMutex));
	
	for(i = 0; i < _cdrReaderd->m_numThreads; ++i)
	{
		pthread_kill(_cdrReaderd->m_threads[i], SIGUSR1);
	}
}

/*----------------------------------------------------*/

static void BeforeExitUiThread(UiReaderContext* _context)
{
	free(_context);
}

/*---------------------------------------------------*/

static void ShutDown(UiReaderContext* _context)
{	
	int msg = SHUT_DOWN;
	
	MsgSend(_context->m_data->m_uiFeederOutChannel, sizeof(int), &msg);
	/*wait for response*/
	msgRecive(_context->m_data->m_uiFeederInChannel, sizeof(int), &msg);
	CloseCdrReaders(_context->m_data, _context->m_cdrReaders);
}

/*----------------------------------------------------*/

static void PauseProcess(RecieverData* _data)
{
	pthread_mutex_lock(&(_data->m_flagMutex));
	_data->m_isPause = 1;
	pthread_mutex_unlock(&(_data->m_flagMutex));
}

/*----------------------------------------------------*/

static void ResumeProcess(RecieverData* _data, Recievers* _cdrReaderd)
{
	size_t i;
	
	pthread_mutex_lock(&(_data->m_flagMutex));
	_data->m_isPause = 0;
	pthread_mutex_unlock(&(_data->m_flagMutex));
	
	for(i = 0; i < _cdrReaderd->m_numThreads; ++i)
	{
		pthread_kill(_cdrReaderd->m_threads[i], SIGUSR1);
	}
}

/*----------------------------------------------------*/

void ResponseOperatorQuery(RecieverData* _data, int _key)
{
	char* response;
	
	response = OperatorRetriveQuery(_data->m_operators, _key);
	if(NULL == response)
	{
		ZLOG(_data->m_log, LOG_CRITICAL, "allocation failed")
		return;
	}
	
	if(MsgSend(_data->m_uiOutChannel, LINE_LENGTH, response) < 0)
	{
		ZLOG(_data->m_log, LOG_CRITICAL, "msg send failed error #%d", errno)
	}
	
	free(response);
}

/*----------------------------------------------------*/

void ResponseSubscriberQuery(RecieverData* _data, char* _key)
{
	char* response;
	
	response = MsisdnRetriveQuery(_data->m_subscribers, _key);
	if(NULL == response)
	{
		ZLOG(_data->m_log, LOG_CRITICAL, "allocation failed")
		return;
	}
	
	if(MsgSend(_data->m_uiOutChannel, LINE_LENGTH, response) < 0)
	{
		ZLOG(_data->m_log, LOG_CRITICAL, "msg send failed error #%d", errno)
	}
	
	free(response);
}

/*----------------------------------------------------*/

void* UIReader(UiReaderContext* _context)
{
	CommendMsg commendData;
	
	InitializeVoidSignal();

	while(!IsEnd(_context->m_data))
	{
		if(msgRecive( _context->m_data->m_uiInChannel, sizeof(CommendMsg), &commendData) < 0)
		{
			ZLOG(_context->m_data->m_log, LOG_CRITICAL, "msg recive failed error #%d", errno)
		}
		switch(commendData.m_commend)
		{
			case MSISDN_RETRIVE:
				ResponseSubscriberQuery(_context->m_data, commendData.m_context);
				break;
				
			case OPERATOR_RETRIVE:
				ResponseOperatorQuery(_context->m_data, atoi(commendData.m_context));
				break;
				
			case ALL_SUBSCIBERS_REPORT:
				AllSubscribersReport(_context->m_data->m_subscribers, _context->m_data->m_outputPath);
				break;
			
			case ALL_OPERATOR_REPORT:
				AllOperatorsReport(_context->m_data->m_operators, _context->m_data->m_outputPath);
				break;
				
			case AGGREGATED_INFORMATION:
				AggregatedInformation(_context->m_data->m_subscribers,
									 _context->m_data->m_operators, _context->m_data->m_outputPath);
				break;
				
			case PAUSE:
				PauseProcess(_context->m_data);
				break;
				
			case RESUME:
				ResumeProcess(_context->m_data, _context->m_cdrReaders);
				break;
				
			case SHUT_DOWN:
				AggregatedInformation(_context->m_data->m_subscribers,
									 _context->m_data->m_operators, _context->m_data->m_outputPath);
				ShutDown(_context);
				break;
		}
	}
	BeforeExitUiThread(_context);
	pthread_exit(NULL);
}

Recievers* CreateUIReadingThreads(RecieverData* _data, Recievers* _cdrReaders)
{
	size_t i;
	Recievers* threads;
	
	UiReaderContext* context = CreateUiReaderContext(_data, _cdrReaders);
	if(NULL == context)
	{
		return NULL;
	}
	
	threads = CreateRecievers(NUM_UI_LISTENERS);
	if(NULL == threads)
	{
		free(context);
		return NULL;
	}
	
	for(i = 0; i < NUM_UI_LISTENERS; ++i)
	{
		if(0 != pthread_create(&(threads->m_threads[i]), NULL, (void * (*)(void *))UIReader, context))
		{
			perror("thread create");
		}
	}
	
	return threads;
}

/*----------------------------------------------------*/

int JoinCdrRecieverThreads(Recievers* _Recievers)
{
	size_t i;
	int status;
	
	for(i = 0; i < _Recievers->m_numThreads; ++i)
	{
		status = pthread_join(_Recievers->m_threads[i] ,NULL);
		if(status != 0)
		{
			fprintf(stderr, "%d thread join failed\n", status);
		}
	}
	DestroyRecievers(_Recievers);
	return 1;
}

/*------------------------------------------------------*/

void DestroyRecieverData(RecieverData* _data)
{
	RetriverDestroy(&(_data->m_operators), (void (*)(void *))DestroyOperator);
	RetriverDestroy(&(_data->m_subscribers), (void (*)(void *))DestroySubscriber);
	DestroyChannel(_data->m_uiInChannel);
	DestroyChannel(_data->m_uiOutChannel);
	DestroyChannel(_data->m_uiFeederInChannel);
	DestroyChannel(_data->m_uiFeederOutChannel);
	DestroyChannel(_data->m_feederChannel);
	pthread_mutex_destroy(&(_data->m_flagMutex));
	free(_data);
}

/*-------------------------------------------------------*/
