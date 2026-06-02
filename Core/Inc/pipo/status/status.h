/*!
 * \file status.h
 * \author Riccardo Segala
 * \date 2026-06-2
 * \brief Module for managing the status LEDs
 */

#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

/*!
 * \brief Bitmask representing the state of all status LEDs.
 *
 * Each bit corresponds to a physical LED:
 * - bit 0 → LED0
 * - bit 1 → LED1
 * - bit 2 → LED2
 */
typedef uint8_t status_led_bitmap;

/*!
 * \brief Callback used to apply LED states to hardware.
 *
 * This function is implemented by the hardware layer and is called
 * whenever the LED bitmap is updated.
 */
typedef void (*status_led_write)(status_led_bitmap);

/*!
 * \brief Return codes for the status module APIs.
 */
enum StatusReturnCode {
    STATUS_RC_OK,           /*!< Operation completed successfully */
    STATUS_RC_INVALID_TYPE, /*!< Invalid status type provided */
    STATUS_RC_NULL_POINTER, /*!< A pointer argument was NULL */
    STATUS_RC_ERROR         /*!< Generic failure */
};

/*!
 * \brief Available system status modes.
 *
 * These values define the LED behavior patterns used to represent
 * system states such as normal operation, flashing warnings, or fatal errors.
 */
enum StatusType {
    STATUS_TYPE_IDLE = 0x00, /*!< Normal operating state (steady/off) */
    STATUS_TYPE_FLASH,       /*!< Flashing status indication */
    STATUS_TYPE_FATAL,       /*!< Fatal error indication */
    STATUS_TYPE_COUNT        /*!< Number of defined status types */
};

/*!
 * \brief Internal state of the status module.
 *
 * This structure stores the current system status, timing information
 * for LED pattern updates, and the hardware callback used to apply
 * LED changes.
 */
struct StatusHandler {
    enum StatusType status; /*!< Current system status mode */

    uint8_t animation_index; /*!< Current index of the active animation */

    status_led_write led_write; /*!< Hardware function used to update LEDs */
};

#endif
