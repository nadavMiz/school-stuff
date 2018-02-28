#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "CGF.h"
#include "subscriber.h"
#include "operator.h"
#include "controller.h" /*LINE_LENGTH*/

#define MAX_PATH_LENGTH 32
#define WORD_BUFFER 128
#define ALL_SUBSCRIBERS_FILE_NAME "subscriber.h"
#define SUBSCRIBER_STR "%s,%u,%u,%u,%u,%u,%u,%u,%u,%f,%f\n\n"
#define OPERATOR_STR "%d,%u,%u,%u,%u\n\n"

static void GetTimeAndDate(char _currentTime[WORD_BUFFER])
{
	struct timeval rawtime;
    struct tm* timeinfo;

    gettimeofday(&rawtime, NULL);
    timeinfo = localtime(&(rawtime.tv_sec));
	
	/*gettimeofday(&currentTime, NULL);*/
	strftime(_currentTime, WORD_BUFFER, "%F %X", timeinfo);
}

static void printHeaderToFile(FILE* _report)
{
	char time[WORD_BUFFER];
	
	GetTimeAndDate(time);
	fprintf(_report, "%s\n\n", time);
}

static void CombineAdressToDest(char* _fileName, const char* _path, char* _dest)
{	
	strcpy(_dest, _path);
	strcat(_dest, _fileName);
}

/*---------------------------------------*/

int WriteSubscriberData(const char* _key, Subscriber* _subscriber, char* _str)
{
	
	sprintf(_str, SUBSCRIBER_STR, _key, _subscriber->m_outCallsWithin, _subscriber->m_inCallsWithin
			 ,_subscriber->m_outCallsOutside, _subscriber->m_inCallsOutside 
			 ,_subscriber->m_msgSentWithin ,_subscriber->m_msgReciveWithin
			 ,_subscriber->m_msgSentOutside ,_subscriber->m_msgReciveOutside 
			 ,_subscriber->m_download ,_subscriber->m_uploads);
	return 1;
}

/*-----------------------------------------*/

int WriteSubscriberDataToFile(const char* _key, Subscriber* _subscriber, FILE* _file)
{
	
	fprintf(_file, SUBSCRIBER_STR, _key, _subscriber->m_outCallsWithin, _subscriber->m_inCallsWithin
			 ,_subscriber->m_outCallsOutside, _subscriber->m_inCallsOutside 
			 ,_subscriber->m_msgSentWithin ,_subscriber->m_msgReciveWithin
			 ,_subscriber->m_msgSentOutside ,_subscriber->m_msgReciveOutside 
			 ,_subscriber->m_download ,_subscriber->m_uploads);
	return 1;
}

/*-----------------------------------------*/

char* MsisdnRetriveQuery(Retriver* _subscribers, char* _msidn)
{
	char* subscriberData;
	
	subscriberData = malloc(sizeof(char) * LINE_LENGTH);
	if(NULL == subscriberData)
	{
		return NULL;
	}
	
	RetriverActionByKey(_subscribers, _msidn, (ActionFunction)WriteSubscriberData, subscriberData);
	
	return subscriberData;
}

/*---------------------------------------------------------*/

int AllSubscribersReport(Retriver* _subscribers, const char* _outputPath)
{
	FILE* report;
	char fileName[MAX_PATH_LENGTH];
	int result;
	
	CombineAdressToDest("subscribers", _outputPath, fileName);
	
	report = fopen(fileName, "w");
	if(NULL == report)
	{
		return 0;
	}
	
	printHeaderToFile(report);
	result = (int)RetriverForEach(_subscribers, (ActionFunction)WriteSubscriberDataToFile, report);
	
	fclose(report);
	return result;
}

/*-----------------------------------------------------------*/

int WriteOperatorData(int* _key, Operator* _operator, char* _str)
{
	sprintf(_str, OPERATOR_STR, *_key, _operator->m_inCalls, _operator->m_outCalls,
			 _operator->m_inMsg, _operator->m_outMsg);
	return 1;
}

/*-----------------------------------------------------------*/

int WriteOperatorDataToFile(int* _key, Operator* _operator, FILE* _file)
{
	fprintf(_file, OPERATOR_STR, *_key, _operator->m_inCalls, _operator->m_outCalls,
			 _operator->m_inMsg, _operator->m_outMsg);
	return 1;
}

/*-----------------------------------------------------------*/

char* OperatorRetriveQuery(Retriver* _operators, int _id)
{
	char* operatorStr;
	
	operatorStr = malloc(sizeof(char) * LINE_LENGTH);
	if(NULL == operatorStr)
	{
		return NULL;
	}
	
	RetriverActionByKey(_operators, &_id, (ActionFunction)WriteOperatorData, operatorStr);
	
	return operatorStr;
}
/*-----------------------------------------------------------*/

int AllOperatorsReport(Retriver* _operators, const char* _outputPath)
{
	FILE* report;
	char fileName[MAX_PATH_LENGTH];
	int result;
	
	CombineAdressToDest("operators", _outputPath, fileName);
	
	report = fopen(fileName, "w");
	if(NULL == report)
	{
		return 0;
	}
	
	printHeaderToFile(report);
	result = (int)RetriverForEach(_operators, (ActionFunction)WriteOperatorDataToFile, report);
	
	fclose(report);
	return result;
}

/*--------------------------------------------------------------*/

int AggregatedInformation(Retriver* _subscribers ,Retriver* _operators, const char* _outputPath)
{
	int allResult = 0;
	int partResult = 0;
	
	partResult = AllSubscribersReport(_subscribers, _outputPath);
	if(0 != partResult)
	{
		allResult = partResult;
	}
	
	partResult = AllOperatorsReport(_operators, _outputPath);
	if(0 != partResult)
	{
		allResult = partResult;
	}
	
	return allResult;
}
