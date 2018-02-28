#ifndef __CDR_PARSER_H__
#define __CDR_PARSER_H__

#define IMSI_LENGTH 16
#define IMES_LENGTH 16
#define MSISDN_LENGTH 16
#define OPERATOR_NAME 65
#define OPERATOR_NUM_LENGTH 7
#define TIME_LENGTH  11
#define LINE_LENGTH 512
#define PATH_SIZE 128

#include <stddef.h>
#include <stdio.h>

#include "zlog4c.h"
#include "communication.h"
#include "queue.h"

typedef enum
{
    MOC =0,
    MTC =1,
    SMS_MO =2,
    SMS_MT =3,
    GPRS = 4
} Calltype;
        
typedef struct ParserThreads ParserThreads;

typedef struct
{
	char m_imsi[IMSI_LENGTH];
	char m_msisdn[MSISDN_LENGTH];
    char m_imei[IMES_LENGTH];
    char m_operatorBrand[OPERATOR_NAME];
    int m_operatorNumber;
    Calltype m_calltype;
    char m_callDate[TIME_LENGTH];
    char m_callTime[TIME_LENGTH];
    size_t m_duration;
    float m_download;
    float m_upload;
    char m_partyMSISDN[MSISDN_LENGTH];
    int m_partyOperator;
} CDRdata; 

/**  
 * @brief gets File name as a string and open the file and move line by line 
 * @param[in] string of file name need to be open
 * @param[out] _line: place to store the line
 *
 * @return success or failure
 * @retval 1: success
 * @retval 0: end of file
 * @retval -1: error accured
 *
 * @warning the file must be opened for reading.
 * @warning line length must be at least LINE_LENGTH or else there is a chance of overflow
 */
int TakeLine(FILE* _stream, char* _line);

/**  
 * @brief parsing a string to defranse value and insert them to struct
 * @param[in] _cdr - string that represent cdr record
 * @param[out] _data - Data struct to fill the data of
 *
 * @return success or failed
 * @retval 1: success
 * @retval 0: invalid cdr format
 *
 * @retval 1: parsing was successful
 * @warning cant get NULL pointers.
 * @warning some fild stay empty.  
 */
int parseCdr(char* _cdr, CDRdata* _data, ZLog _log);

ParserThreads* CreateParseThreads(Queue* _input, Channel _output, char* _outputPath, ZLog _log);

int JoinParseThreads(ParserThreads* _threads);

void PauseParseThreads(ParserThreads* _threads);

void ResumeParseThreads(ParserThreads* _threads, int _signal);

/**
 * @warning sigur1 signal must be set to be a void signal
 */
void CloseParseThreads(ParserThreads* _threads, int _signal);

#endif /* __CDR_PARSER_H__ */
