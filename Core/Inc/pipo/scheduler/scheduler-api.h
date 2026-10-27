/*!
 * \file scheduler-api.h
 * \author Mario Mazzara
 * \date 2026-10-27
 * \brief APIs for the scheduler to manage tasks and watchdogs
 */

#ifndef SCHEDULER_API_H
#define SCHEDULER_API_H

#include "scheduler.h"

/*!
 * \brief Initializes the task scheduler.
 *
 * \details Initializes the timebase and registers the configured tasks.
 *
 * \retval SCHEDULER_RC_OK Initialization succeeded.
 * \retval SCHEDULER_RC_ERROR Initialization failed.
 */
enum SchedulerReturnCode scheduler_api_init(void);

/*!
 * \brief Runs scheduled tasks that are due.
 *
 * \details Call regularly from the main loop.
 *
 * \retval TASKS_RC_OK The routine completed successfully.
 * \retval TASKS_RC_ERROR The task scheduler encountered an error. 
 * \retval TASKS_RC_TEMPORAL_DISCONTINUITY The user tried to travel to the past
 * \retval TASKS_RC_NULL_POINTER A null pointer was passed as argument to the task api
 */
enum TasksReturnCode scheduler_api_routine(void);

/*!
 * \brief Advances the scheduler tick.
 *
 * \details Call from the periodic timer interrupt.
 *
 * \retval TIMEBASE_RC_OK The tick was advanced.
 * \retval TIMEBASE_RC_DISABLED The timebase is disabled.
 * \retval TIMEBASE_RC_NULL_POINTER The timebase handler is null.
 */
enum TimebaseReturnCode scheduler_api_increase_tick(void);

/*!
 * \brief Returns the current scheduler tick.
 *
 * \details The tick count is maintained by the scheduler timebase.
 *
 * \returns uint32_t The number of ticks, if the timebase_handler pointer is NULL, returns 0
 */
uint32_t scheduler_api_get_tick(void);

#endif
