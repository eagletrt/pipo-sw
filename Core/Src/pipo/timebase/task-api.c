#include "task-api.h"
#include "timebase-api.h"

bool task_api_is_ready(struct Task *task) {
    return task->active && (timebase_api_get_ticks() >= task->next_execution) && (task->start_delay <= timebase_api_get_ticks());
}
