#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h>
#include <time.h>
#include <unistd.h>

#include "myTime.h"

/* function to run a task with. gets _context as input. and returns 0 if it should be run again or any other value otherwise*/
typedef int (*TaskFunction) (void* _context); 

typedef struct
{
	TaskFunction m_task;
	void* m_context;
	Time* m_nextTime;
	Time* m_interval;
} Task;

/*************************/
/*Task API FUNCTIONS*/
/*************************/

/**
 @brief create a new task instence
 @param[in] _taskFuncion - function for the task to run
 @param[in] _context - context to run the function with
 @param[in] _period_ms - the interval to wait before running the fun
 */
Task* TaskCreate(TaskFunction _taskFuncion, void* _context, size_t _period_ms, const clockid_t clockID);

/**
 * @brief: safely destroys a task.
 * @param[in] _task: the task to destroy
 * @return void.
 */
void TaskDestroy(Task* _task);

/**
 * @brief calculate the next time to run the task.
 * @param[in] _task - the task to calculate the next time of.
 * @param[in] clockID - the clock_id to calculate the time by
 * @return void.
 */
void TaskCalculateNext(Task* _task, const clockid_t clockID);

/**
 * @brief excecute the function holded by task
 * @param[in] _task: the task to excecute the function of
 * @param[in] clockID: clock_id to calculate the time by
 */
int	TaskExecute(Task* _task, const clockid_t clockID);

/**
 * @brief checks if _a is smaller than _b (if _a is scheduelled to run before _b)
 * @param[in] _a: the task to check if smaller
 * @param[in] _b: the task to comparer _a to.
 * @return 0 if a is smaller than b. 0 otherwise
 */
int	TaskLessThan(Task* _a, Task* _b);

#endif /* __TASK_H */

