/*!
 * \file tasks.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief Module for managing the feedback signals of the system
 */

#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>

#define TASKS_COUNT 1

typedef uint32_t tick;

typedef void (*task_callback)(void);

/*!
 * \brief Return codes for the tasks module APIs.
 */
enum TasksReturnCode {
    TASKS_RC_OK,   /*!< Operation completed successfully */
    TASKS_RC_ERROR /*!< Generic failure */
};

struct TasksTask {
    tick start_delay;
    tick period;
    tick last_execution;
    task_callback callback;
};

/*!
 * \brief Internal state of the tasks module.
 */
struct TasksHandler {
    tick current_tick;
};

#endif
