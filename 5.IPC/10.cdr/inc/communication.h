#ifndef __MESSEGE_H__
#define __MESSEGE_H__

#define FTOK_FILE "../ftokfile"
#define FEEDER_CHANNEL 3
#define UI_TO_PROCESSOR_CHANNEL 1
#define UI_FROM_PROCESSOR_CHANNEL 2
#define CDR_MOVER_CHANNEL 3
#define PROCESSOR_TO_FEEDER 4
#define FEEDER_TO_PROCESSOR 5

#include "stddef.h"

typedef int Channel;

int CreateChannel(int _id);

int GetChannel(int _id);

void DestroyChannel(Channel _channel);

int MsgSend(int _channel, size_t _size, void* _data);

int msgRecive(Channel _channel, size_t _dataSize, void* _data);

#endif /* __MESSEGE_H__ */
