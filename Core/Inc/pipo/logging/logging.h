#ifndef LOGGING_H
#define LOGGING_H

/*!
 * \file logging.h
 * \author Mario Mazzara
 * \date 2026-10-27
 * \brief Types for hardware-independent logging.
 */

/*!
 * \brief Output callback used by the logging module.
 * \param[in] str Null-terminated text to send to the output.
 */
typedef void (*logging_log)(const char *str);

/*! \brief Stores the configured logging output callback. */
struct LoggingHandler {
    logging_log log; /*!< Function used to emit log text */
};

/*! \brief Results returned by the logging module. */
enum LoggingReturnCode {
    LOGGING_RC_NULL_POINTER, /*!< The output callback was null */
    LOGGING_RC_OK            /*!< The operation succeeded */
};
#endif // !LOGGING_H
