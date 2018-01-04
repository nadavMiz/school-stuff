#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "Task.h"

typedef struct PeriodicExecutor PeriodicExecutor;

/**
 * @brief creates a new periodic excecuter
 * @param[in] _name: name of the ne executer
 * @param[in] _clk_id: clock id to calculate the time by
 * @return pointer to a new periodic excecuter
 */
PeriodicExecutor* PeriodicExecutorCreate(const char* _name, clockid_t _clk_id);

/**
 * @brief dafely destroys a periodic executer
 * @param[in] _executor: pointer to the executer to destroy
 * @return void.
 */
void PeriodicExecutorDestroy(PeriodicExecutor* _executor);

/**
 * @brief adds a new function for the periodic executer to run
 * @param[in] _executor: the executer to run the function
 * @param[in] _taskFunction: the function to run (returns 0 if it should be run again, any other value otherwise)
 * @param[in] _context: context to run the function with.
 * @param[in] _period_ms: time to wait between when the function was entered to when it should run
 * @return 1 if the task was entered successfully. 0 otherwise
 */
int PeriodicExccutorAdd(PeriodicExecutor* _executor, TaskFunction _taskFunction, void* _context, size_t _period_ms); 

/**
 * @brief runs a periodic Executor until it ran all its tasks or until pause was requested
 * @param[in] _executor: the executer to run
 * @return number of tasks that ran before it stopped
 */
size_t PeriodicExccutorRun(PeriodicExecutor* _executor);

/**
 * @brief pauses a periodic executer. should be entered as a function for the executer to run
 * @param[in] _executor: the executer to pause.
 * @return number of tasks left for the executer to run.
 */
size_t PeriodicExccutorPause(PeriodicExecutor* _executor);


#endif /* __SCHEDULER_H__ */
