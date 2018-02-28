#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "processorConfigParser.h"

static ProcessorConfigue* CreatDefaultStruct()
{
	ProcessorConfigue* processorConfig = malloc(sizeof(ProcessorConfigue));
	if(NULL == processorConfig)
	{
		return NULL;
	}
	
	strcpy(processorConfig->m_reportPath, DEFAULT_REPORT_PATH);
	processorConfig->m_numThreads = DEFAULT_NUM_CDR_READING_THREADS;
	
	return processorConfig;
}

/*------------------------------------------------------------------------------------------*/

static void ReadSection(FILE* _config, ProcessorConfigue* _ProcessorConfig)
{
	char inputVal[WORD_SIZE], inputName[WORD_SIZE];
	
	/*check if the module is correct*/
	do
	{
		fgets(inputVal, WORD_SIZE, _config);
		
	} while(1 != sscanf(inputVal, "[%[^]]]", inputVal) || strcmp(PROCESSOR_HEADER, inputVal) || feof(_config));
	if(feof(_config))
	{
		return;
	}
	
	/*get the feeder values*/
	while(2 == fscanf(_config, "%s = %s", inputName, inputVal))
	{
		if( 0== strcmp(inputName, "reportPath"))
		{
			strcpy(_ProcessorConfig->m_reportPath, inputVal);
		}
		else if(0 == strcmp(inputName, "NumCDRreadingThreads"))
		{
			_ProcessorConfig->m_numThreads = (size_t)atoi(inputVal);
		}
	}
}

/*-----------------------------------------------------------------------------------------*/

ProcessorConfigue* ParseProcessorConfigue(char* _configFilePath)
{
	ProcessorConfigue* processorStruct;
	FILE* config;
	
	processorStruct = CreatDefaultStruct();
	if(NULL == processorStruct)
	{
		return NULL;
	}
	
	config = fopen(_configFilePath, "r");
	if(NULL == config)
	{
		perror("open file");
		return processorStruct;
	}
	
	ReadSection(config, processorStruct);
	
	fclose(config);
	
	return processorStruct;
}

/*--------------------------------------------------*/

void DestroyProcessorConfig(ProcessorConfigue* _processorStruct)
{
	free(_processorStruct);
}
