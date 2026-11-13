/*!
 * \file task-api.h
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief This module provides the APIs for the tasks 
 */

#ifndef TASK_API_H
#define TASK_API_H

#include "task.h"

#include <stdbool.h>

/*!
 * \brief Places a task into the linker task section.
 */
#define TASK_API_SECTION \
    __attribute__((section(".tasks"), aligned(sizeof(void *))))

/*!
 * \brief Registers a task in the task section.
 *
 * \param name Task instance name.
 * \param delay Initial start delay in ticks.
 * \param task_period Execution period in ticks.
 * \param task_callback Task callback function.
 */
#define TASK_API_REGISTER(name, delay, task_period, task_callback) \
    struct Task name TASK_API_SECTION = {                          \
        .active = true,                                            \
        .start_delay = (delay),                                    \
        .period = (task_period),                                   \
        .next_execution = 0,                                       \
        .callback = (task_callback),                               \
    }

/*!
 * \brief Determines whether a task is ready for execution.
 *
 * A task is considered ready when:
 * - it is active,
 * - its start delay has elapsed,
 * - its next execution time has been reached.
 *
 * \param task Pointer to the task instance.
 *
 * \return true if the task is ready to execute, false otherwise.
 */
bool task_api_is_ready(struct Task *task);

#endif
