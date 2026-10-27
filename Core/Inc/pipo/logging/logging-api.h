#ifndef LOGGING_API_H
#define LOGGING_API_H

/*!
 * \file logging-api.h
 * \author Mario Mazzara
 * \date 2026-10-27
 * \brief Public API for configuring and using logging.
 */

#include "logging.h"
#include "common.h"

/*!
 * \brief Configures the logging output.
 * \param[in] log Callback that sends text to the selected output.
 * \retval LOGGING_RC_OK The callback was configured.
 * \retval LOGGING_RC_NULL_POINTER The callback was null.
 */
enum LoggingReturnCode logging_api_init(logging_log log);

/*!
 * \brief Prints a list of voltage values.
 * \details Values are space-separated and followed by a newline. No output is
 * produced if \p volts is null or logging has not been initialized.
 * \param[in] volts Array of voltage values.
 * \param[in] size Number of values in \p volts.
 */
void logging_api_print_voltages(const voltage *volts, size_t size);
#endif // !LOGGING_API_H
