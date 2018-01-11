#ifndef __SUMARRIZER_H__
#define __SUMARRIZER_H__

#include "retriver.h"

/**
 * @brief: create file for a single subscriber containing its data
 * @param[in] _subscribers: retriver containing the subscribers data
 * @param[in] _msidn: MSIDN of the subscriber
 * @param[in] _outputPath: output path to save the file to
 */
char* MsisdnRetriveQuery(Retriver* _subscribers, char* _msidn);

/**
 * @brief: create file for a single operator containing its data
 * @param[in] _id: MMC/MNC of the operator
 * @param[in] _operators: retriver containing the operators data
 * @param[in] _outputPath: output path to save the file to
 */
char* OperatorRetriveQuery(Retriver* _operators, int _id);

/**
 * @brief: create report containing aggregate data of all subscribers
 * @param[in] _subscribers: retriver containing the subscribers data
 * @param[in] _outputPath: path to save the report to
 */
int AllSubscribersReport(Retriver* _subscribers, const char* _outputPath);

/**
 * @brief: creates report containing the aggregated data of all operators
 * @param[in] _operators: retriver containing th operators data
 * @param[in] _outputPath: path to save the report to
 */
int AllOperatorsReport(Retriver* _operators, const char* _outputPath);

/**
 * @brief: creates two files. one with the aggregated data of all operators.
 *         and one with the aggregate data of all subscribers
 * @param[in] operators: retriver containing th operators data
 * @param[in] _subscribers: retriver containing the subscribers data
 * @param[in] _outputPath: path to save the files to
 */
int AggregatedInformation(Retriver* _subscribers ,Retriver* _operators, const char* _outputPath);

#endif /* __SUMARRIZER_H__ */
