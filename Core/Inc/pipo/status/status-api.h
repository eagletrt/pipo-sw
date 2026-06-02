/*!
 * \file status-api.h
 * \author Riccardo Segala
 * \date 2026-06-2
 * \brief This module provides the APIs for controlling the status LEDs
 */

#ifndef STATUS_API_H
#define STATUS_API_H

#include "status.h"

/*!
 * \brief Initializes the status module.
 *
 * Sets the internal state to a known default value and initializes
 * the hardware callback if configured.
 *
 * \param[in] led_write the function used to set the leds (hardware dependent)
 * \retval STATUS_RC_NULL_POINTER if the write_callback argument is null.
 * \retval STATUS_RC_OK on successful initialization.
 */
enum StatusReturnCode status_init(const status_led_write led_write);

/*!
 * \brief Executes the status update routine.
 *
 * This function updates LED behavior based on the current status mode
 * and internal timing (e.g. blinking patterns). It should be called
 * periodically from the main loop or scheduler.
 */
void status_routine(void);

/*!
 * \brief Sets the current system status mode.
 *
 * This function changes the active status state (e.g. idle, flash, fatal),
 * which determines the LED behavior pattern applied by the routine.
 *
 * \param[in] status New status mode to apply.
 * \retval STATUS_RC_INVALID_TYPE if the status does not exist.
 * \retval STATUS_RC_OK on success.
 */
enum StatusReturnCode status_set_status(const enum StatusType status);

#endif
