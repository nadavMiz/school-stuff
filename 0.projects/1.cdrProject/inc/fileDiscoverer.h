#ifndef __FILE_DISCOVERER_H__
#define __FILE_DISCOVERER_H__

#define PATH_SIZE 128

#include <pthread.h>

#include "communication.h"
#include "zlog4c.h"
#include "queue.h"

typedef struct Discoverer Discoverer;

typedef struct
{
	char m_fileName[PATH_SIZE];
	char m_filePath[PATH_SIZE];
} FilePathName;

Discoverer* CreateFileDiscovererThread(Queue* _output, char* _inputPath, char* _outputPath,
										char* _invalidPath , char* _mask ,ZLog _log);

void CloseFileDiscoverer(Discoverer* _discoverer, int _signal);

int JoinFileDiscoverer(Discoverer* _discoverer);

void PauseFileDiscoverer(Discoverer* _discoverer);

void ResumeFileDiscoverer(Discoverer* _discoverer, int _signal);

#endif /* __FILE_DISCOVERER_H__ */
