#include <string.h>
#include <stdlib.h>

#include "subscriber.h"
#include "CDRparser.h"
#include "operator.h" /*for operator match*/

typedef void (*AddData) (Subscriber* _subscriber, CDRdata* _data);


Subscriber* CreateSubscriber()
{
	Subscriber* newSubscriber = calloc(1, sizeof(Subscriber));
	if(NULL == newSubscriber)
	{
		return NULL;
	}
	return newSubscriber;
}

/*-------------------------------------------------------*/

void DestroySubscriber(Subscriber* _subscriber)
{
	free(_subscriber);
}

/*--------------------------------------------------------*/

char* GetSubscriberKey(CDRdata* _data)
{
	char* key = malloc(sizeof(char) * IMSI_LENGTH);
	if(NULL == key)
	{
		fprintf(stderr,"allocation error\n");
		return NULL;
	}
	
	strcpy(key, _data->m_msisdn);
	return key;
}

/*--------------------------------------------------------*/

void DestroySubscriberKey(char* _key)
{
	free(_key);
}

/*--------------------------------------------------------*/

size_t SubscriberHash(const char* _key)
{
    long hash = 5381;
    int c;

    while (c = *_key++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (size_t)hash;
}

/*-------------------------------------------------------*/

int SubscriberMatch(const char* _a, const char* _b)
{
	return (0 == strcmp(_a, _b));
}

/*--------------------------------------------------------*/

static void AddMoc(Subscriber* _subscriber, CDRdata* _data)
{
	if(_data->m_partyOperator == _data->m_operatorNumber)
	{
		_subscriber->m_outCallsWithin += _data->m_duration;
	}
	else
	{
		_subscriber->m_outCallsOutside += _data->m_duration;
	}
}

static void AddMtc(Subscriber* _subscriber, CDRdata* _data)
{
	if(_data->m_partyOperator == _data->m_operatorNumber)
	{
		_subscriber->m_inCallsWithin += _data->m_duration;
	}
	else
	{
		_subscriber->m_inCallsOutside += _data->m_duration;
	}
}

static void AddSmsOut(Subscriber* _subscriber, CDRdata* _data)
{
	if(_data->m_partyOperator == _data->m_operatorNumber)
	{
		++_subscriber->m_msgSentWithin;
	}
	else
	{
		++_subscriber->m_msgSentOutside;
	}
}

static void AddSmsIn(Subscriber* _subscriber, CDRdata* _data)
{
	if(_data->m_partyOperator == _data->m_operatorNumber)
	{
		++_subscriber->m_msgReciveWithin;
	}
	else
	{
		++_subscriber->m_msgReciveOutside;
	}
}

static void AddInternet(Subscriber* _subscriber, CDRdata* _data)
{
	_subscriber->m_download += _data->m_download;
	_subscriber->m_uploads += _data->m_upload;
}

void SubscriberAddData(Subscriber* _subscriber, CDRdata* _data)
{
	static AddData AddFunctions[] = {AddMoc, AddMtc, AddSmsOut, AddSmsIn, AddInternet};
	
	AddFunctions[_data->m_calltype](_subscriber, _data);
}

