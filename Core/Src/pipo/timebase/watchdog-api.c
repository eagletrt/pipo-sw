
/*!
 * \file watchdog-api.c
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief Watchdog API implementation
 */

#include "watchdog-api.h"
#include "timebase-api.h"
#include "timebase.h"

#include <stddef.h>

enum WatchdogReturnCode watchdog_api_init_watchdog(struct Watchdog *watchdog, timebase_tick timeout) {

    if (watchdog == NULL) {
        return WATCHDOG_RC_ERROR;
    }

    watchdog->active = false;
    watchdog->expiration = 0U;
    watchdog->timeout = timeout;

    return WATCHDOG_RC_OK;
}

enum WatchdogReturnCode watchdog_api_start(struct Watchdog *watchdog) {
    if (watchdog == NULL) {
        return WATCHDOG_RC_ERROR;
    }

    watchdog->expiration = timebase_api_get_ticks() + watchdog->timeout;
    watchdog->active = true;

    return WATCHDOG_RC_OK;
}

enum WatchdogReturnCode watchdog_api_stop(struct Watchdog *watchdog) {

    if (watchdog == NULL) {
        return WATCHDOG_RC_ERROR;
    }

    watchdog->active = false;

    return WATCHDOG_RC_OK;
}

bool watchdog_api_is_expired(const struct Watchdog *watchdog) {

    if ((watchdog == NULL) || (!watchdog->active)) {
        return false;
    }

    return (timebase_api_get_ticks() >= watchdog->expiration);
}

bool watchdog_api_is_active(const struct Watchdog *watchdog) {

    if (watchdog == NULL) {
        return false;
    }

    return watchdog->active;
}
