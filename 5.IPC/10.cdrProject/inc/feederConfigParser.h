#ifndef __FEEDER_CONFIG_H__
#define __FEEDER_CONFIG_H__

#define WORD_SIZE 128
#define MASK_SIZE 8 
#define FEEDER_HEADER "feeder"
#define DEFAULT_INPUT_PATH "inputFiles"
#define DEFAULT_OUTPUT_PATH "doneFiles"
#define DEFAULT_INVALID_PATH "invalidFiles"
#define DEFAULT_FILE_MASK ".cdr"
#define DEFAULT_NUM_PARSER_THREADS 3 

typedef struct
{
	char m_inputPath[WORD_SIZE];
	char m_outputPath[WORD_SIZE];
	char m_invalidPath[WORD_SIZE];
	char m_mask[MASK_SIZE];
	size_t m_numThreads;
	
} FeederConfigue;

FeederConfigue* ParseFeederConfigue(char* _configFilePath);

void DestroyFeederConfig(FeederConfigue* _feederStruct);

#endif /* __CONFIG_H__ */
