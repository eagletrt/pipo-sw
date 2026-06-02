/*!
 * \file post.h
 * \author Riccardo Segala
 * \date 2026-06-2
 * \brief Module for managing system initialization and power-on self-test (POST)
 */

#ifndef POST_H
#define POST_H

#include "status.h"

/*!
 * \brief Return codes for the POST module APIs.
 */
enum PostReturnCode {
    POST_RC_OK,    /*!< Operation completed successfully */
    POST_RC_ERROR, /*!< Operation not completed */
};

/*!
 * \brief Initialization data required by the POST module.
 *
 * This structure contains hardware-dependent callbacks and configuration
 * parameters required during system initialization.
 */
struct PostInitData {
    status_led_write led_write; /*!< Callback used to update the status LEDs */
};

#endif
