#ifndef __OPERATOR_H__
#define __OPERATOR_H__

#include "CDRparser.h"

typedef struct
{
	char*  m_brand;
	size_t m_inCalls;
	size_t m_outCalls;
	size_t m_inMsg;
	size_t m_outMsg;
} Operator;

/**
 * @brief: creates a new operator with 0 in all fields
 * @return new operator. NULL if allocation failed
 */
Operator* CreateOperator();

/**
 * @brief: destroys an operator
 * @param[in] _opertor - operator to destroy
 * @return void
 */
void DestroyOperator(Operator* _opertor);

size_t OperatorHash(const int* _id);

int OperatorMatch(const int* _Akey, const int* _Bkey);

/**
 * @brief: get the operators MCC/MID(key) from a cdr data
 * @param[in] _data - CDR data to extract the key from
 * @return pointer to the operators key
 * @warning stores the key in heap(remember to destroy)
 */
int* GetOperatorKey(CDRdata* _data);

/**
 * @brief: detroys an operator key
 * @param[in] _key - destroys a key
 * @return: void
 */
void DestroyOperatorKey(int* _key);

/**
 * @brief: adds relvent data from a CDRdata struct to an operator.
 * @param[in] _operator - operator to add the data to
 * @param[in] _data - CDRdata struct to add data from
 * @return: void
 * @warning: doesnt check the operators MCC/MID(key). has to enter the right operator. 
 */
void OperatorAddData(Operator* _operator, CDRdata* _data);


#endif /* __OPERATOR_H__ */
