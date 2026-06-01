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
 * \brief Get a line voltage.
 * \param[in] index The line index.
 * \param[out] value Pointer where the voltage will be stored.
 * \retval LINES_RC_OK on success.
 * \retval LINES_RC_OUT_OF_BOUNDS if the index is out of range.
 * \retval LINES_RC_NULL_POINTER if value is null.
 */
enum LinesReturnCode lines_api_get_line_voltage(const size_t index, voltage *value);

/*!
 * \brief Get the line voltages array.
 * \param[out] size Number of elements in the array.
 * \note The value pointed by the size pointer won't be updated in case of null pointer
 * \return Pointer to the line voltages array.
 */
const voltage *lines_api_get_line_voltages(size_t *size);

/*!
 * \brief Get a line current.
 * \param[in] index The line index.
 * \param[out] value Pointer where the current will be stored.
 * \retval LINES_RC_OK on success.
 * \retval LINES_RC_OUT_OF_BOUNDS if the index is out of range.
 * \retval LINES_RC_NULL_POINTER if value is null.
 */
enum LinesReturnCode lines_api_get_line_current(const size_t index, current *value);

/*!
 * \brief Get the line currents array.
 * \param[out] size Number of elements in the array.
 * \note The value pointed by the size pointer won't be updated in case of null pointer
 * \return Pointer to the line currents array.
 */
const current *lines_api_get_line_currents(size_t *size);

#endif
