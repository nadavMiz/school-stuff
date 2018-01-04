#ifndef __Z_LOG__
#define __Z_LOG__

#include <stdio.h>
#include <unistd.h>

#include "config.h"

#define BUFFER_SIZE 1024
#define WORD_BUFFER 128
#define NUM_LOG_LEVELS 9

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvariadic-macros"

#define ZLOG(LOG, LEVEL, ...) \
	char msg[WORD_BUFFER];\
	sprintf(msg, __VA_ARGS__);\
 	WriteEntry(LOG, LEVEL, __func__, __FILE__, __LINE__, msg);
 	
#pragma GCC diagnostic pop

typedef enum
{
	LOG_TRACE = 0,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL,
	LOG_SEVERE,
	LOG_FATAL,
	LOG_NONE
} LogLevel;

typedef struct ZLogData* ZLog;

ZLog ZLogGet(char* _moduleName, char* _configFilePath);

void WriteEntry(ZLog _log, int _level, const char* _func, const char* _file, int _line, const char* fmt);

/*-----------test functions--------------------*/

void PrintLogsData();

#endif /*__Z_LOG__*/
