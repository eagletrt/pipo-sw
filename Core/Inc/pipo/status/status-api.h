/*!
 * \file status-api.h
 * \author Riccardo Segala
 * \author Mario Mazzara
 * \date 2026-10-27
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
enum StatusReturnCode status_api_init(const status_led_write led_write);

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
enum StatusReturnCode status_api_set_status(const enum StatusType status);

/*!
 * \brief update leds periodic task function
 * 
 * \param[in] task_id
 */
void status_api_task_led(uint8_t task_id);

/*!
 * \brief send data data to can periodic task function
 * 
 * \param[in] task_id
 */
void status_api_task_can(uint8_t task_id);

#endif
