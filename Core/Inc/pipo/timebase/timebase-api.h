/*!
 * \file timebase-api.h
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief This module provides the APIs for the timebase module
 */

#ifndef TIMEBASE_API_H
#define TIMEBASE_API_H

#include "timebase.h"

/*!
 * \brief Initializes the task scheduler.
 *
 * This function initializes the internal timebase handler
 *
 * \return TIMEBASE_RC_OK on successful initialization.
 */
enum TimebaseReturnCode timebase_api_init(void);

/*!
 * \brief Executes the timebase routine.
 *
 * This function is intended to be called as often as possible.
 *
 * \note This function must be kept fast and non-blocking.
 */
void timebase_api_routine(void);

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
void timebase_api_tick(void);

/*!
 * \brief Returns the current system tick count.
 *
 * This function retrieves the current value of the system timebase counter.
 * The returned tick value is typically incremented by a hardware timer interrupt
 * and represents the elapsed time since system initialization in tick units.
 *
 * \return Current system tick count.
 */
timebase_tick timebase_api_get_ticks(void);

#endif
