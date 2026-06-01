/*!
 * \file lines-api.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief This module provides the APIs for the lines module
 */

#ifndef LINES_API_H
#define LINES_API_H

#include "lines.h"

#include <stddef.h>

/*!
 * \brief Initializes the lines internal handler and resets all values to zero.
 * \return LINES_RC_OK on successful initialization.
 */
enum LinesReturnCode lines_api_init(void);

/*!
 * \brief Update the low power line voltage.
 * \param[in] value The voltage of the line in V.
 * \retval LINES_RC_OK on success.
 */
enum LinesReturnCode lines_api_update_low_power_voltage(const voltage value);

/*!
 * \brief Update the high power line voltage.
 * \param[in] value The voltage of the line in V.
 * \retval LINES_RC_OK on success.
 */
enum LinesReturnCode lines_api_update_high_power_voltage(const voltage value);

/*!
 * \brief Update the autonomous system line voltage.
 * \param[in] value The voltage of the line in V.
 * \retval LINES_RC_OK on success.
 */
enum LinesReturnCode lines_api_update_autonomous_system_voltage(const voltage value);

/*!
 * \brief Update a line voltage.
 * \param[in] index The line index.
 * \param[in] value The voltage of a line in V.
 * \retval LINES_RC_OK on success.
 * \retval LINES_RC_OUT_OF_BOUNDS if the index is out of range.
 */
enum LinesReturnCode lines_api_update_line_voltage(const size_t index, const voltage value);

/*!
 * \brief Update lines' voltage.
 * \param[in] index The line index.
 * \param[in] values The voltages of the lines in V.
 * \param[in] size The size of the values array.
 * \retval LINES_RC_OK on success.
 * \retval LINES_RC_OUT_OF_BOUNDS if the index + size is out of range.
 * \retval LINES_RC_NULL_POINTER if the values array is null.
 */
enum LinesReturnCode lines_api_update_line_voltages(const size_t index, const voltage *values, const size_t size);

/*!
 * \brief Update a line current.
 * \param[in] index The line index.
 * \param[in] value The current of a line in A.
 * \retval LINES_RC_OK on success.
 * \retval LINES_RC_OUT_OF_BOUNDS if the index is out of range.
 */
enum LinesReturnCode lines_api_update_line_current(const size_t index, const current value);

/*!
 * \brief Update lines' current.
 * \param[in] index The line index.
 * \param[in] values The currents of the lines in A.
 * \param[in] size The size of the values array.
 * \retval LINES_RC_OK on success.
 * \retval LINES_RC_OUT_OF_BOUNDS if the index + size is out of range.
 * \retval LINES_RC_NULL_POINTER if the values array is null.
 */
enum LinesReturnCode lines_api_update_line_currents(const size_t index, const current *values, const size_t size);

/*!
 * \brief Get the low power line voltage.
 * \return The low power line voltage in V.
 */
voltage lines_api_get_low_power_voltage(void);

/*!
 * \brief Get the high power line voltage.
 * \return The high power line voltage in V.
 */
voltage lines_api_get_high_power_voltage(void);

/*!
 * \brief Get the autonomous system line voltage.
 * \return The autonomous system line voltage in V.
 */
voltage lines_api_get_autonomous_system_voltage(void);

/*!
 * \brief Get the line voltages array.
 * \param[out] size Number of elements in the array.
 * \note The value pointed by the size pointer won't be updated in case of null pointer
 * \return Pointer to the line voltages array.
 */
const voltage *lines_api_get_line_voltages(size_t *size);

/*!
 * \brief Get the line currents array.
 * \param[out] size Number of elements in the array.
 * \note The value pointed by the size pointer won't be updated in case of null pointer
 * \return Pointer to the line currents array.
 */
const current *lines_api_get_line_currents(size_t *size);

#endif
