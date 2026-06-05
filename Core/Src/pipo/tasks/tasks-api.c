/*!
 * \file tasks-api.c
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief Implementation of the tasks module APIs
 */

#include "tasks-api.h"
#include "eagletrt.h"
#include "tasks.h"
#include "usart.h"

#include <string.h>

extern struct TasksTask __tasks_start;
extern struct TasksTask __tasks_end;

EAGLETRT_STATIC struct TasksHandler handler;

enum TasksReturnCode tasks_api_init(void) {

    memset(&handler, 0, sizeof(handler));

    return TASKS_RC_OK;
}

void tasks_api_routine(void) {

    struct TasksTask *current_task = &__tasks_start;

    while (current_task < &__tasks_end) {
        if ((handler.current_tick - current_task->last_execution) >= current_task->period) {

            current_task->last_execution = handler.current_tick;

            if (current_task->callback != nullptr) {
                current_task->callback();
            }
        }

        current_task++;
    }
}

void tasks_api_tick(void) {
    handler.current_tick++;
}
