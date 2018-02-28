#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "feederConfigParser.h"

static FeederConfigue* CreatDefaultStruct()
{
	FeederConfigue* feederConfig = malloc(sizeof(FeederConfigue));
	if(NULL == feederConfig)
	{
		return NULL;
	}
	
	strcpy(feederConfig->m_inputPath, DEFAULT_INPUT_PATH);
	strcpy(feederConfig->m_outputPath, DEFAULT_OUTPUT_PATH);
	strcpy(feederConfig->m_invalidPath, DEFAULT_INVALID_PATH);
	strcpy(feederConfig->m_mask, DEFAULT_FILE_MASK);
	feederConfig->m_numThreads = DEFAULT_NUM_PARSER_THREADS;
	
	return feederConfig;
}

/*------------------------------------------------------------------------------------------*/

static void ReadSection(FILE* _config, FeederConfigue* _feederConfig)
{
	char inputVal[WORD_SIZE], inputName[WORD_SIZE];
	
	/*check if the module is correct*/
	do
	{
		fgets(inputVal, WORD_SIZE, _config);
		
	} while(1 != sscanf(inputVal, "[%[^]]]", inputVal) || strcmp(FEEDER_HEADER, inputVal) || feof(_config));
	if(feof(_config))
	{
		return;
	}
	
	/*get the feeder values*/
	while(2 == fscanf(_config, "%s = %s", inputName, inputVal))
	{
		if( 0== strcmp(inputName, "inputPath"))
		{
			strcpy(_feederConfig->m_inputPath, inputVal);
		}
		else if(0 == strcmp(inputName, "donePath"))
		{
			strcpy(_feederConfig->m_outputPath, inputVal);
		}
		else if(0 == strcmp(inputName, "invalidPath"))
		{
			strcpy(_feederConfig->m_invalidPath, inputVal);
		}
		else if(0 == strcmp(inputName, "fileMask"))
		{
			strcpy(_feederConfig->m_mask, (inputVal + 1));
		}
		else if(0 == strcmp(inputName, "NumCDRParsingThreads"))
		{
			_feederConfig->m_numThreads = (size_t)atoi(inputVal);
		}
	}
}

/*-----------------------------------------------------------------------------------------*/

FeederConfigue* ParseFeederConfigue(char* _configFilePath)
{
	FeederConfigue* feederStruct;
	FILE* config;
	
	feederStruct = CreatDefaultStruct();
	if(NULL == feederStruct)
	{
		return NULL;
	}
	
	config = fopen(_configFilePath, "r");
	if(NULL == config)
	{
		perror("open file");
		return feederStruct;
	}
	
	ReadSection(config, feederStruct);
	
	fclose(config);
	
	return feederStruct;
}

/*--------------------------------------------------*/

void DestroyFeederConfig(FeederConfigue* _feederStruct)
{
	free(_feederStruct);
}
