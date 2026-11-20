#ifndef PIPO_FSM_H
#define PIPO_FSM_H

enum PipoFsmStates {
    PIPO_FSM_INIT,
    PIPO_FSM_IDLE,
    PIPO_FSM_FLASH,
    PIPO_FSM_FATAL,
    PIPO_FSM_STATE_COUNT
};
enum PipoFsmReturnCode {
    PIPO_FSM_RC_OK,
    PIPO_FSM_RC_ERROR,
    PIPO_FSM_RC_NULL_POINTER
};
#endif // PIPO_FSM_H
