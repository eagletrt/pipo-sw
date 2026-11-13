/*!
 * \file timebase.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief Module for managing the timebase module for tasks and watchdogs
 */

#ifndef TIMEBASE_H
#define TIMEBASE_H

#include <stdint.h>

typedef uint32_t timebase_tick;

/*!
 * \brief Return codes for the timebase module APIs.
 */
enum TimebaseReturnCode {
    TIMEBASE_RC_OK,   /*!< Operation completed successfully */
    TIMEBASE_RC_ERROR /*!< Generic failure */
};

/*!
 * \brief Internal state of the timebase module.
 */
struct TimebaseHandler {
    timebase_tick current_tick;
};

#endif
