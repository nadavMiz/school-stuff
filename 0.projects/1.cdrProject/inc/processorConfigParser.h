#ifndef __PROCESSOR_CONFIG_H__
#define __PROCESSOR_CONFIG_H__

#define WORD_SIZE 128
#define PROCESSOR_HEADER "processor"
#define DEFAULT_REPORT_PATH "../inputFiles"
#define DEFAULT_NUM_CDR_READING_THREADS 4 

typedef struct
{
	char m_reportPath[WORD_SIZE];
	size_t m_numThreads;
	
} ProcessorConfigue;

ProcessorConfigue* ParseProcessorConfigue(char* _configFilePath);

void DestroyProcessorConfig(ProcessorConfigue* _processorStruct);

#endif /* __CONFIG_H__ */
