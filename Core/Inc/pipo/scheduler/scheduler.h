/*!
 * \file scheduler.h
 * \author Mario Mazzara 
 * \date 2026-10-27
 * \brief Module for managing tasks and watchdogs
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#define SCHEDULER_MS_RESOLUTION (1U)

#include <stdint.h>

#include "tasks.h"
#include "timebase.h"

/*! \brief IDs for the tasks registered with the scheduler. */
enum TaskList {
    TASK_STATUS_LED = 0,
    TASK_STATUS_CAN,
    TASK_FEEDBACK_CAN,
    TASK_ACQUISITION_UPDATE_DATA,
    TASK_ACQUISITION_PRINT_DATA,
    TASK_COUNT
};

/*!
 * \brief Return codes for the scheduler module APIs.
 */
enum SchedulerReturnCode {
    SCHEDULER_RC_OK,   /*!< Operation completed successfully */
    SCHEDULER_RC_ERROR /*!< Generic failure */
};

/*!
 * \brief Internal state of the scheduler module.
 */
struct SchedulerHandler {
    struct TimebaseHandler timebase; /*!< Tick counter used by tasks and watchdogs */
    struct TasksHandler tasks;       /*!< Registered task state and schedule */
};

#endif
