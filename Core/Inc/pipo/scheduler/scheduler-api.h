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
 * \details Initializes the timebase, configured tasks, watchdog pool, and one
 * watchdog with a timeout of 100 ticks.
 * \param ms_resolution Duration of one timebase tick, in milliseconds.
 * \param watchdog_callback Function called when the watchdog times out.
 *
 * \retval SCHEDULER_RC_OK Initialization succeeded.
 * \retval SCHEDULER_RC_ERROR Initialization failed.
 */
enum SchedulerReturnCode scheduler_api_init(uint32_t ms_resolution, watchdog_timeout_callback watchdog_callback);

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
 * \return Current tick count. Each tick represents \p ms_resolution milliseconds
 * as provided to scheduler_api_init.
 */
uint32_t scheduler_api_get_tick(void);

/*!
 * \brief Starts the scheduler watchdog.
 * \details Starts the watchdog configured by scheduler_api_init.
 * \retval WATCHDOG_RC_OK The watchdog started.
 * \retval WATCHDOG_RC_BUSY The watchdog is already running.
 * \retval WATCHDOG_RC_TIMED_OUT The watchdog has already timed out.
 * \retval WATCHDOG_RC_TEMPORAL_DISCONTINUITY The tick count moved backwards.
 * \retval WATCHDOG_RC_NULL_POINTER The watchdog tick getter is unavailable.
 * \retval WATCHDOG_RC_UNINITIALIZED The scheduler watchdog is not initialized.
 * \retval WATCHDOG_RC_ERROR The watchdog could not be scheduled.
 */
enum WatchdogReturnCode scheduler_api_watchdog_start(void);

/*!
 * \brief Stops the scheduler watchdog.
 * \retval WATCHDOG_RC_OK The watchdog stopped.
 * \retval WATCHDOG_RC_NOT_RUNNING The watchdog is not running.
 * \retval WATCHDOG_RC_TIMED_OUT The watchdog has already timed out.
 * \retval WATCHDOG_RC_NULL_POINTER A required watchdog pointer is null.
 * \retval WATCHDOG_RC_UNINITIALIZED The scheduler watchdog is not initialized.
 * \retval WATCHDOG_RC_ERROR The watchdog could not be removed from the schedule.
 */
enum WatchdogReturnCode scheduler_api_watchdog_stop(void);

/*!
 * \brief Feeds the scheduler watchdog to extend its deadline.
 * \retval WATCHDOG_RC_OK The watchdog deadline was extended.
 * \retval WATCHDOG_RC_NOT_RUNNING The watchdog is not running.
 * \retval WATCHDOG_RC_TIMED_OUT The watchdog has already timed out.
 * \retval WATCHDOG_RC_TEMPORAL_DISCONTINUITY The tick count moved backwards.
 * \retval WATCHDOG_RC_NULL_POINTER The watchdog tick getter is unavailable.
 * \retval WATCHDOG_RC_UNINITIALIZED The scheduler watchdog is not initialized.
 * \retval WATCHDOG_RC_ERROR The watchdog could not be rescheduled.
 */
enum WatchdogReturnCode scheduler_api_watchdog_feed(void);

#endif
