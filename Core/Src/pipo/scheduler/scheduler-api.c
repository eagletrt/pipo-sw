/*!
 * \file scheduler-api.c
 * \author Mario Mazzara
 * \date 2026-10-26
 * \brief Implementation of the scheduler module APIs
 */

#include "scheduler-api.h"

#include "eagletrt.h"
#include "can-primary.h"
#include "tasks-api.h"
#include "timebase-api.h"

#include "acquisition-api.h"
#include "feedback-api.h"
#include "status-api.h"

#include <string.h>


EAGLETRT_STATIC struct SchedulerHandler handler;

EAGLETRT_STATIC TaskList task_list = {
    {
        .task_id = TASK_STATUS_LED,
        .state = TASKS_STATE_ENABLED,
        .repeats = 0U,
        .function = status_api_task_led,
        .interval = 200U,
        .start = 0U,
    },
    {
        .task_id = TASK_STATUS_CAN,
        .state = TASKS_STATE_ENABLED,
        .repeats = 0U,
        .function = status_api_task_can,
        .interval = can_primary_cycle_time_pipofsm,
        .start = 5U,
    },
    {
        .task_id = TASK_FEEDBACK_CAN,
        .state = TASKS_STATE_ENABLED,
        .repeats = 0U,
        .function = feedbacks_api_task_can,
        .interval = can_primary_cycle_time_piposhutdown,
        .start = 5U,
    },
    {
        .task_id = TASK_ACQUISITION_UPDATE_DATA,
        .state = TASKS_STATE_ENABLED,
        .repeats = 0U,
        .function = acquisition_api_task_update_data,
        .interval = 100U,
        .start = 0U,
    },
    {
        .task_id = TASK_ACQUISITION_PRINT_DATA,
        .state = TASKS_STATE_ENABLED,
        .repeats = 0U,
        .function = acquisition_api_task_print_data,
        .interval = 1000U,
        .start = 0U,
    },
};

EAGLETRT_STATIC uint32_t prv_get_tick(void) {
    return timebase_get_tick(&handler.timebase);
}

enum SchedulerReturnCode scheduler_api_init(void) {
    memset(&handler, 0, sizeof(handler));

    if (timebase_api_init(&handler.timebase, SCHEDULER_MS_RESOLUTION) != TIMEBASE_RC_OK ||
        timebase_set_enable(&handler.timebase, true) != TIMEBASE_RC_OK) {
        return SCHEDULER_RC_ERROR;
    }

    if (tasks_api_init(&handler.tasks, task_list, TASK_COUNT, prv_get_tick) != TASKS_RC_OK) {
        return SCHEDULER_RC_ERROR;
    }

    return SCHEDULER_RC_OK;
}

enum TasksReturnCode scheduler_api_routine(void) {
    return tasks_api_routine(&handler.tasks);
}

enum TimebaseReturnCode scheduler_api_increase_tick(void) {
    return timebase_inc_tick(&handler.timebase);
}

uint32_t scheduler_api_get_tick(void) {
    return timebase_get_tick(&handler.timebase);
}
