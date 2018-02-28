#ifndef __CDR_RECIEVER_H__
#define __CDR_RECIEVER_H__

#include "processorConfigParser.h"

typedef struct Recievers Recievers;

typedef struct RecieverData RecieverData;



RecieverData* CDRreciverInit(ProcessorConfigue* _config);

void CDRreciverDestroy(RecieverData* _data);

Recievers* CreateCdrReadingThreads(RecieverData* _data);

Recievers* CreateUIReadingThreads(RecieverData* _data, Recievers* _cdrReaders);

int JoinCdrRecieverThreads(Recievers* _recievers);

void DestroyRecieverData(RecieverData* _data);


#endif /* __CDR_RECIEVER_H__ */
