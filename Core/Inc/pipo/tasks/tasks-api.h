/*!
 * \file tasks-api.h
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief This module provides the APIs for the task scheduler
 */

#ifndef TASKS_API_H
#define TASKS_API_H

#include "tasks.h"

/*!
 * \brief Initializes the task scheduler.
 *
 * This function initializes the internal task handler and prepares all
 * registered tasks for execution by resetting timing information.
 *
 * \return TASKS_RC_OK on successful initialization.
 */
enum TasksReturnCode tasks_init(void);

/*!
 * \brief Executes the task scheduler routine.
 *
 * This function is intended to be called as often as possible.
 * It iterates over all registered tasks and executes those
 * whose period has elapsed based on the system tick counter.
 *
 * \note This function must be kept fast and non-blocking.
 */
void tasks_routine(void);

/*!
 * \brief Increments the system tick counter.
 *
 * This function is typically called from a hardware timer interrupt
 * (e.g., SysTick every 1ms). It updates the internal time base used
 * by the scheduler to determine when tasks are due for execution.
 *
 * \note Must be called from a time-critical interrupt context.
 * \note Should remain as short as possible (increment only).
 */
void tasks_tick(void);

#endif
