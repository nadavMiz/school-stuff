#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

#include "CDRparser.h"

typedef struct 
{
	size_t m_outCallsWithin;
	size_t m_inCallsWithin;
	size_t m_outCallsOutside;
	size_t m_inCallsOutside; 
	size_t m_msgSentWithin;
	size_t m_msgReciveWithin;
	size_t m_msgSentOutside;
	size_t m_msgReciveOutside;
	double m_download;
	double m_uploads;
	
} Subscriber;

Subscriber* CreateSubscriber();

void DestroySubscriber(Subscriber* _subscriber);

char* GetSubscriberKey(CDRdata* _data);

void DestroySubscriberKey(char* _key);

void SubscriberAddData(Subscriber* _subscriber, CDRdata* _data);

size_t SubscriberHash(const char* _key);

int SubscriberMatch(const char* _a, const char* _b);
#endif /* __SUBSCRIBER_H__ */ 
