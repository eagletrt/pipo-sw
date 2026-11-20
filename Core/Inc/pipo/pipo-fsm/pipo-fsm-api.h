#ifndef PIPO_FSM_API_H
#define PIPO_FSM_API_H
#include "pipo-fsm.h"
#include "eagletrt-fsm.h"

enum FSMReturnCode pipo_fsm_api_run_state(void *data);
enum PipoFsmStates pipo_fsm_api_get_state();
enum PipoFsmReturnCode pipo_fsm_api_init();

#endif // PIPO_FSM_API_H
