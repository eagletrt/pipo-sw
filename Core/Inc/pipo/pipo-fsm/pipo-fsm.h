/*!
 * \file pipo-fsm.h
 * \author Mario Mazzara
 * \date 2026-11-23
 * \brief State identifiers and return codes for the Pipo FSM.
 */

#ifndef PIPO_FSM_H
#define PIPO_FSM_H

/*! \brief States used by the Pipo FSM. */
enum PipoFsmStates {
    PIPO_FSM_INIT,       /*!< Performs startup initialization */
    PIPO_FSM_IDLE,       /*!< Runs normal scheduled tasks */
    PIPO_FSM_FLASH,      /*!< Reserved for bootloader integration */
    PIPO_FSM_FATAL,      /*!< Holds the system in a fatal state */
    PIPO_FSM_STATE_COUNT /*!< Number of FSM states */
};

/*! \brief Results returned by the Pipo FSM API. */
enum PipoFsmReturnCode {
    PIPO_FSM_RC_OK,          /*!< Operation completed successfully */
    PIPO_FSM_RC_ERROR,       /*!< FSM initialization failed */
    PIPO_FSM_RC_NULL_POINTER /*!< A required pointer was null */
};

#endif // PIPO_FSM_H
