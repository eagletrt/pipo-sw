/*!
 * \file watchdog-api.h
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief This module provides the APIs for the watchdog module
 */

#ifndef WATCHDOG_API_H
#define WATCHDOG_API_H

#include "timebase.h"
#include "watchdog.h"

/*!
 * \brief Initializes a watchdog instance.
 *
 * \param watchdog Pointer to the watchdog instance.
 * \param timeout Timeout in ticks.
 *
 * \return WATCHDOG_RC_OK on success.
 */
enum WatchdogReturnCode watchdog_api_init_watchdog(struct Watchdog *watchdog, timebase_tick timeout);

/*!
 * \brief Starts or restarts a watchdog.
 *
 * The watchdog will expire after the specified timeout.
 *
 * \param watchdog Pointer to the watchdog instance.
 *
 * \return WATCHDOG_RC_OK on success.
 */
enum WatchdogReturnCode watchdog_api_start(struct Watchdog *watchdog);

/*!
 * \brief Stops a watchdog.
 *
 * \param watchdog Pointer to the watchdog instance.
 *
 * \return WATCHDOG_RC_OK on success.
 */
enum WatchdogReturnCode watchdog_api_stop(struct Watchdog *watchdog);

/*!
 * \brief Checks whether a watchdog has expired.
 *
 * \param watchdog Pointer to the watchdog instance.
 *
 * \return true if the watchdog has expired, false otherwise.
 */
bool watchdog_api_is_expired(const struct Watchdog *watchdog);

/*!
 * \brief Checks whether a watchdog is active.
 *
 * \param watchdog Pointer to the watchdog instance.
 *
 * \return true if the watchdog is active, false otherwise.
 */
bool watchdog_api_is_active(const struct Watchdog *watchdog);

#endif
