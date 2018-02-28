#ifndef __CONFIG_H__
#define __CONFIG_H__

#define WORD_SIZE 128
#define DEFAULT_INPUT_PATH "/cdr"
#define DEFAULT_OUTPUT_PATH "/billing"

typedef struct
{
	char m_inputPath[WORD_SIZE];
	char m_outputPath[WORD_SIZE];
	char m_fileMask[WORD_SIZE];
	
} ConfigueStruct;

/**
 * @brief: parse a configuration file
 * @param[in] _configFilePath: path of configue file to parse
 * @return: structure containing the parsed data
 */
ConfigueStruct* ParseConfigue(char* _configFilePath);

/**
 * @brief: destroys a ConfigueStruct
 * @param[in] ConfigueStruct to destroy
 * @return: void
 */
void DestroyConfigStruct(ConfigueStruct* _configueStruct);

#endif /* __CONFIG_H__ */
