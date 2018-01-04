#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> /*perror*/

#include "barrier.h"

#define MAGIC_NUMBER 0XCDEF113A
#define IS_BARRIER(B) (NULL != (B) && MAGIC_NUMBER == (B)->m_magicNumber)

typedef struct
{
	pthread_cond_t* m_barrier;
	size_t m_countIn;
	size_t m_IsOut;
} GateData;

struct Barrier
{
	pthread_cond_t* m_batchCond;
	pthread_mutex_t* m_mutex;
	GateData* m_gateIn;
	GateData* m_gateOut;
	size_t m_magicNumber;
	size_t m_capacity;
	size_t m_batchCounter;
	size_t m_currentBatch;
};

/*-----------------------------------------------------------------*/

static pthread_cond_t* CreateCond()
{
	pthread_cond_t* newCond = malloc(sizeof(pthread_cond_t));
	if(NULL == newCond)
	{
		return NULL;
	}
	
	if(pthread_cond_init(newCond, NULL) < 0)
	{
		perror("cond init");
		free(newCond);
		return NULL;
	}
	
	return newCond;
}

static void DestroyCond(pthread_cond_t* _cond)
{
	if(pthread_cond_destroy(_cond) < 0)
	{
		perror("cond destroy");
	}
	free(_cond);
}

static pthread_mutex_t* CreateMutex()
{
	pthread_mutex_t* newMutex = malloc(sizeof(pthread_mutex_t));
	if(NULL == newMutex)
	{
		return NULL;
	}

	if(pthread_mutex_init(newMutex, NULL) < 0)
	{
		perror("mutex init");
		free(newMutex);
		return NULL;
	}

	return newMutex;
}

static void DestroyMutex(pthread_mutex_t* _mutex)
{
	if(pthread_mutex_destroy(_mutex) < 0)
	{
		perror("mutex destroy");
	}
	free(_mutex);
}

static GateData* CreateGateData()
{
	GateData* newGateData;
	pthread_cond_t* cond;
	
	newGateData = malloc(sizeof(GateData));
	if(NULL == newGateData)
	{
		fprintf(stderr, "barrier malloc failed\n");
		return NULL;
	}
	
	cond = CreateCond();
	if(NULL == cond)
	{
		free(newGateData);
		return NULL;
	}
	
	newGateData->m_barrier = cond;
	newGateData->m_countIn = 0;
	newGateData->m_IsOut = 0;
	
	return newGateData;
}

static void DestroyGateData(GateData* _data)
{
	DestroyCond(_data->m_barrier);
	free(_data);
}

/*---------------------------------------------------------------*/

Barrier* BarrierCreate(unsigned int _capacity)
{
	Barrier* newBarrier;
	
	newBarrier = malloc(sizeof(Barrier));
	if(NULL == newBarrier)
	{
		fprintf(stderr, "barrier malloc failed\n");
		return NULL;
	}
	
	newBarrier->m_batchCond = CreateCond();
	if(NULL == newBarrier->m_batchCond)
	{
		free(newBarrier);
		return NULL;
	}
	
	newBarrier->m_mutex = CreateMutex();
	if(NULL == newBarrier->m_mutex)
	{
		DestroyCond(newBarrier->m_batchCond);
		free(newBarrier);
		return NULL;
	}
	
	newBarrier->m_gateIn = CreateGateData();
	if(NULL == newBarrier->m_gateIn)
	{
		DestroyMutex(newBarrier->m_mutex);
		DestroyCond(newBarrier->m_batchCond);
		free(newBarrier);
		return NULL;
	}
	
	newBarrier->m_gateOut = CreateGateData();
	if(NULL == newBarrier->m_gateOut)
	{
		DestroyMutex(newBarrier->m_mutex);
		DestroyCond(newBarrier->m_batchCond);
		DestroyGateData(newBarrier->m_gateIn);
		free(newBarrier);
		return NULL;
	}
	
	newBarrier->m_batchCounter = 0;
	newBarrier->m_currentBatch = 0;
	newBarrier->m_capacity = _capacity;
	newBarrier->m_magicNumber = MAGIC_NUMBER;
	
	return newBarrier;
}

void BarrierDestroy(Barrier* _barrier)
{
	DestroyMutex(_barrier->m_mutex);
	DestroyCond(_barrier->m_batchCond);
	DestroyGateData(_barrier->m_gateIn);
	DestroyGateData(_barrier->m_gateOut);
	free(_barrier);
	_barrier->m_magicNumber = 0;
	free(_barrier);
}

/*-----------------------------------------------------------*/

static size_t GetBatch(Barrier* _barrier)
{
	size_t result = _barrier->m_batchCounter / _barrier->m_capacity;
	++_barrier->m_batchCounter;
	return result;
}

/*-----------------------------------------------------------*/

static int BatchGate(Barrier* _barrier)
{
	size_t batch;
	
	batch = GetBatch(_barrier);
	
	while(batch != _barrier->m_currentBatch)
	{
		if(pthread_cond_wait(_barrier->m_batchCond, _barrier->m_mutex) < 0)
		{
			pthread_mutex_unlock(_barrier->m_mutex);
			perror("wait batch gate");
			return -1;
		} 
	}
	return 1;
}

/*------------------------------------------------------------*/

static int Gate(GateData* _gate, Barrier* _barrier, int _isEnd)
{
	++(_gate->m_countIn);
	if(_gate->m_countIn == _barrier->m_capacity)
	{
		_gate->m_IsOut = 1;
		if(pthread_cond_broadcast(_gate->m_barrier) < 0)
		{
			perror("cond broadcast");
			return -1;
		}
	}
	else
	{
		while(!(_gate->m_IsOut))
		{
			if(pthread_cond_wait(_gate->m_barrier, _barrier->m_mutex) < 0)
			{
				pthread_mutex_unlock(_barrier->m_mutex);
				perror("wait batch gate");
				return -1;
			} 
		}
	}
	--_gate->m_countIn;
	if(_gate->m_countIn == 0)
	{
		_gate->m_IsOut = 0;
		_gate->m_countIn = 0;
		if(_isEnd)
		{
			++(_barrier->m_currentBatch);
			if(pthread_cond_broadcast(_barrier->m_batchCond) < 0)
			{
				perror("cond broadcast");
				return -1;
			}
		}
	}
	return 1;
}

/*----------------------------------------------------------------------*/

int BarrierWait(Barrier* _barrier, void(*_ActionFunc)(void*), void* _context)
{
	pthread_mutex_lock(_barrier->m_mutex);
	
	if(-1 == BatchGate(_barrier))
	{
		return -1;
	}
	
	if(-1 == Gate(_barrier->m_gateIn, _barrier, 0))
	{
		return -1;
	}
	pthread_mutex_unlock(_barrier->m_mutex);
	
	if(NULL != _ActionFunc)
	{
		_ActionFunc(_context);
	}
	
	pthread_mutex_lock(_barrier->m_mutex);
	
	if(-1 == Gate(_barrier->m_gateOut, _barrier, 1))
	{
		return -1;
	}
	
	pthread_mutex_unlock(_barrier->m_mutex);
	
	return 1;
}
