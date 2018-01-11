#include <stdlib.h>
#include <string.h>

#include "operator.h"
#include "CDRparser.h"

Operator* CreateOperator(CDRdata* _data)
{
	Operator* newOperator = calloc(1, sizeof(Operator));
	if(NULL == newOperator)
	{
		return NULL;
	}
	
	newOperator->m_brand = malloc(OPERATOR_NAME * sizeof(char));
	if(NULL == newOperator->m_brand)
	{
		free(newOperator);
		return NULL;
	}
	
	return newOperator;
}

/*---------------------------------*/

void DestroyOperator(Operator* _operator)
{
	if(NULL == _operator)
	{
		return;
	}
	free(_operator->m_brand);
	free(_operator);
}

/*---------------------------------*/

int* GetOperatorKey(CDRdata* _data)
{
	int* key = malloc(sizeof(int));
	if(NULL == key)
	{
		fprintf(stderr,"allocation error\n");
		return NULL;
	}

	*key = _data->m_partyOperator;
	return key;
}

/*---------------------------------*/

void DestroyOperatorKey(int* _key)
{
	free(_key);
}

/*---------------------------------*/

void OperatorAddData(Operator* _operator, CDRdata* _data)
{
	switch(_data->m_calltype)
	{
		case MOC:
			_operator->m_outCalls += _data->m_duration;
			break;
		case MTC:
			_operator->m_inCalls += _data->m_duration;
			break;
		case SMS_MO:
			++_operator->m_outMsg;
			break;
		case SMS_MT:
			++_operator->m_inMsg;
		default:
			break;
	}
}

/*-----------------------------------*/

size_t OperatorHash(const int* _id)
{
	return (size_t)(*_id);	
}

int OperatorMatch(const int* _Akey, const int* _Bkey)
{
	return (*_Akey == *_Bkey);
}

