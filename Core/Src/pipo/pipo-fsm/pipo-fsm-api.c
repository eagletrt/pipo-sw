#include "eagletrt-api.h"
#include "eagletrt-fsm-api.h"
#include "pipo-fsm-api.h"
#include "eagletrt-fsm.h"
#include "post-api.h"
#include "scheduler-api.h"
#include "tasks.h"

EAGLETRT_STATIC struct FSMHandler fsm_handler;

void prv_start_tasks(void *data) {
    EAGLETRT_API_UNUSED(data);
    scheduler_api_task_start(TASK_STATUS_LED);
    scheduler_api_task_start(TASK_STATUS_CAN);
    scheduler_api_task_start(TASK_FEEDBACK_CAN);
    scheduler_api_task_start(TASK_ACQUISITION_UPDATE_DATA);
    scheduler_api_task_start(TASK_ACQUISITION_PRINT_DATA);
}
void prv_stop_tasks(void *data) {
    EAGLETRT_API_UNUSED(data);
    scheduler_api_task_stop(TASK_STATUS_LED);
    scheduler_api_task_stop(TASK_STATUS_CAN);
    scheduler_api_task_stop(TASK_FEEDBACK_CAN);
    scheduler_api_task_stop(TASK_ACQUISITION_UPDATE_DATA);
    scheduler_api_task_stop(TASK_ACQUISITION_PRINT_DATA);
}

// _______ INIT ______
constexpr size_t init_transition_list_size = 2;
struct Transition init_transition_list[init_transition_list_size] = {
    { .to = PIPO_FSM_IDLE, .function = prv_start_tasks },
    { .to = PIPO_FSM_FATAL, .function = NULL },
};
void prv_init(void *data) {
    enum PostReturnCode rc = post_api_run((struct PostInitData *)data);
    if (rc != POST_RC_OK) {
        fsm_api_transition_to(&fsm_handler, PIPO_FSM_FATAL);
    } else {
        fsm_api_transition_to(&fsm_handler, PIPO_FSM_IDLE);
    }
}
// ___________________

// _______ IDLE ______
constexpr size_t idle_transition_list_size = 2;
struct Transition idle_transition_list[idle_transition_list_size] = {
    { .to = PIPO_FSM_FLASH, .function = prv_stop_tasks },
    { .to = PIPO_FSM_FATAL, .function = prv_stop_tasks },
};

void prv_idle(void *data) {
    EAGLETRT_API_UNUSED(data);
    enum TasksReturnCode rc = scheduler_api_task_routine();
    if (rc != TASKS_RC_OK) {
        fsm_api_transition_to(&fsm_handler, PIPO_FSM_FATAL);
    }
}
// ___________________

// ______ FLASH ______
constexpr size_t flash_transition_list_size = 2;
struct Transition flash_transition_list[flash_transition_list_size] = {
    { .to = PIPO_FSM_IDLE, .function = prv_start_tasks },
    { .to = PIPO_FSM_FATAL, .function = NULL },
};

void prv_flash(void *data) {
    EAGLETRT_API_UNUSED(data);
    return;
}
// ___________________

// ______ FATAL ______
struct Transition fatal_to_fatal = { .to = PIPO_FSM_FATAL, .function = NULL };
void prv_fatal(void *data) {
    EAGLETRT_API_UNUSED(data);
    return;
}
// ___________________

struct State state_list[PIPO_FSM_STATE_COUNT] = {
    { .id = PIPO_FSM_INIT,
      .function = prv_init,
      .next_default = PIPO_FSM_INIT,
      .transitions = init_transition_list,
      .num_transitions = init_transition_list_size },
    { .id = PIPO_FSM_IDLE,
      .function = prv_idle,
      .next_default = PIPO_FSM_IDLE,
      .transitions = idle_transition_list,
      .num_transitions = idle_transition_list_size },
    { .id = PIPO_FSM_FLASH,
      .function = prv_flash,
      .next_default = PIPO_FSM_FLASH,
      .transitions = flash_transition_list,
      .num_transitions = flash_transition_list_size },
    { .id = PIPO_FSM_FATAL,
      .function = prv_fatal,
      .next_default = PIPO_FSM_FATAL,
      .transitions = &fatal_to_fatal,
      .num_transitions = 1 }
};

enum PipoFsmReturnCode pipo_fsm_api_init() {
    enum FSMReturnCode rc = fsm_api_init(&fsm_handler, state_list, PIPO_FSM_STATE_COUNT, PIPO_FSM_INIT);
    if (rc != FSM_RC_OK) {
        return PIPO_FSM_RC_ERROR;
    }
    return PIPO_FSM_RC_OK;
}
enum PipoFsmStates pipo_fsm_api_get_state() {
    return (enum PipoFsmStates)fsm_api_get_state(&fsm_handler);
}
enum FSMReturnCode pipo_fsm_api_run_state(void *data) {
    return fsm_api_run_state(&fsm_handler, data);
}
