/*!
 * \file feedbacks.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief Module for managing the feedback signals of the system
 */

#ifndef FEEDBACKS_H
#define FEEDBACKS_H

typedef float voltage;

/*!
 * \brief Return codes for the feedbacks module APIs.
 */
enum FeedbacksReturnCode {
    FEEDBACKS_RC_OK,            /*!< Operation completed successfully */
    FEEDBACKS_RC_OUT_OF_BOUNDS, /*!< Index/type is outside valid range */
    FEEDBACKS_RC_INVALID_TYPE,  /*!< Invalid feedback type provided */
    FEEDBACKS_RC_NULL_POINTER,  /*!< Null pointer passed as argument */
    FEEDBACKS_RC_ERROR          /*!< Generic failure */
};

/*!
 * \brief Identifiers for the available feedback signals.
 *
 * These represent the different digital/analog feedback channels
 * monitored by the system, including power rails and shutdown signals.
 */
enum FeedbacksType {
    FEEDBACK_TYPE_5V = 0x00,     /*!< 5 V supply feedback signal */
    FEEDBACK_TYPE_ASMS,          /*!< ASMS (Autonomous System Master Switch) feedback*/
    FEEDBACK_TYPE_RES_GO,        /*!< RES (Reset Enable Signal) GO feedback */
    FEEDBACK_TYPE_SHUTDOWN_BSPD, /*!< BSPD shutdown circuit feedback */
    FEEDBACK_TYPE_SHUTDOWN_TSMS, /*!< TSMS shutdown circuit feedback */
    FEEDBACK_TYPE_SHUTDOWN_HVD,  /*!< HVD shutdown circuit feedback */
    FEEDBACK_TYPE_SHUTDOWN_OUT,  /*!< Shutdown output feedback signal */
    FEEDBACK_TYPE_COUNT          /*!< Number of feedback channels */
};

/*!
 * \brief Internal state of the feedbacks module.
 *
 * This structure holds the latest sampled voltage values for all
 * feedback channels in the system. Indexing is done using FeedbackType.
 */
struct FeedbacksHandler {
    voltage feedbacks[FEEDBACK_TYPE_COUNT]; /*!< Feedback voltages in volts (V) */
};

#endif
