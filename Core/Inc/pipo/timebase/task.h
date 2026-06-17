/*!
 * \file task.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief Module for managing the tasks
 */

#ifndef TASK_H
#define TASK_H

#include "timebase.h"

#include <stdint.h>

typedef void (*task_callback)(void);

/*!
 * \brief Return codes for the tasks module APIs.
 */
enum TaskReturnCode {
    TASKS_RC_OK,   /*!< Operation completed successfully */
    TASKS_RC_ERROR /*!< Generic failure */
};

struct Task {
    bool active;
    timebase_tick start_delay;
    timebase_tick period;
    timebase_tick next_execution;
    task_callback callback;
};

#endif
