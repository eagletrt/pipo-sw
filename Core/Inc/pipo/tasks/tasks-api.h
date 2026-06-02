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
 * This function is intended to be called periodically (e.g., from a
 * hardware timer interrupt every 1ms). It iterates over all registered
 * tasks and executes those whose period has elapsed.
 *
 * \note This function must be fast and non-blocking.
 */
void tasks_routine(void);

#endif
