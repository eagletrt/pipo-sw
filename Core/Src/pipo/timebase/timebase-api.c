/*!
 * \file timebase-api.c
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief Implementation of the timebase module APIs
 */

#include "eagletrt.h"
#include "timebase.h"
#include "task-api.h"
#include "usart.h"

#include <string.h>

extern struct Task __tasks_start;
extern struct Task __tasks_end;

EAGLETRT_STATIC struct TimebaseHandler handler;

enum TimebaseReturnCode timebase_api_init(void) {

    memset(&handler, 0, sizeof(handler));

    return TIMEBASE_RC_OK;
}

void timebase_api_routine(void) {

    struct Task *current_task = &__tasks_start;

    while (current_task < &__tasks_end) {
        if (task_api_is_ready(current_task)) {

            if (current_task->callback != nullptr) {
                current_task->callback();
            }

            if (current_task->period > 0) {
                current_task->next_execution += current_task->period;
            } else {
                current_task->active = false;
            }
        }

        current_task++;
    }
}

void timebase_api_tick(void) {
    handler.current_tick++;
}

timebase_tick timebase_api_get_ticks(void) {
    return handler.current_tick;
}
