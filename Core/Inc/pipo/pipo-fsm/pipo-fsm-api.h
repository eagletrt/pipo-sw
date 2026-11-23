/*!
 * \file pipo-fsm-api.c
 * \author Mario Mazzara
 * \date 2026-11-23
 * \brief Public API for controlling the Pipo FSM.
 */
#ifndef PIPO_FSM_API_H
#define PIPO_FSM_API_H

#include "pipo-fsm.h"
#include "eagletrt-fsm.h"

/*!
 * \brief Runs the current FSM state.
 * \details Pass initialization data on the first run; later state runs may use
 * null when the state does not need external data.
 * \param data Data passed to the current state's callback.
 * \retval FSM_RC_OK The state ran successfully.
 * \retval FSM_RC_INVALID_TRANSITION The requested transition is not configured.
 * \retval FSM_RC_NULL_POINTER The FSM handler is not initialized.
 */
enum FSMReturnCode pipo_fsm_api_run_state(void *data);

/*!
 * \brief Returns the current FSM state.
 * \return Current state identifier.
 */
enum PipoFsmStates pipo_fsm_api_get_state(void);

/*!
 * \brief Initializes the Pipo FSM.
 * \details Sets the initial state to \p PIPO_FSM_INIT.
 * \retval PIPO_FSM_RC_OK The FSM was initialized.
 * \retval PIPO_FSM_RC_ERROR The FSM state table is invalid.
 */
enum PipoFsmReturnCode pipo_fsm_api_init(void);

#endif // PIPO_FSM_API_H
