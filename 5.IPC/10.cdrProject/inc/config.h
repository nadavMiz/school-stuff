#ifndef __CONFIG_H__
#define __CONFIG_H__

#define WORD_SIZE 128
#define DEFAULT_MODULE_NAME "#"
#define DEFAULT_LEVEL "LOG_ERROR"
#define DEFAULT_FILE_NAME "log.log"

typedef struct
{
	char m_path[WORD_SIZE];
	char m_level[WORD_SIZE];
	char m_module[WORD_SIZE];
	
} ConfigueStruct;

ConfigueStruct* ParseConfigue(char* _configFilePath);

void DestroyConfigStruct(ConfigueStruct* _logStruct);

#endif /* __CONFIG_H__ */
