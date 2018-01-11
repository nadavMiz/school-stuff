#ifndef __FEEDER_WATCHDOG_H__
#define __FEEDER_WATCHDOG_H__

#include "communication.h"
#include "pthread.h"
#include "CDRparser.h"
#include "fileDiscoverer.h"

typedef struct WachDogThread WachDogThread;

WachDogThread* CreateWatchdog(Channel _uiInChannel, Channel _uiOutChannel,
							 ParserThreads* _parsers, Discoverer* _discoverer);

void JoinWatchDog(WachDogThread* _watchdog);

#endif /* __FEEDER_WATCHDOG_H__ */
