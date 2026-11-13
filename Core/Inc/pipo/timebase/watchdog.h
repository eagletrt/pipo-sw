/*!
 * \file watchdog.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief Module for managing the watchdogs
 */

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "timebase.h"

#include <stdint.h>

/*!
 * \brief Return codes for the watchdog module APIs.
 */
enum WatchdogReturnCode {
    WATCHDOG_RC_OK,   /*!< Operation completed successfully */
    WATCHDOG_RC_ERROR /*!< Generic failure */
};

struct Watchdog {
    bool active;
    timebase_tick expiration;
    timebase_tick timeout;
};

#endif
