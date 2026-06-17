/*!
 * \file feedbacks-api.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief This module provides the APIs for the feedbacks module
 */

#include "feedbacks.h"

#include <stddef.h>

/*!
 * \brief Initializes the feedbacks internal handler and resets all values to zero.
 * \return FEEDBACKS_RC_OK on successful initialization.
 */
enum FeedbacksReturnCode feedbacks_api_init(void);

/*!
 * \brief Update a feedback voltage.
 * \param[in] type The type of the feedback to update.
 * \param[in] value The voltage of a feedback in V.
 * \retval FEEDBACKS_RC_OK on success.
 * \retval FEEDBACKS_RC_OUT_OF_BOUNDS if the index is out of range.
 */
enum FeedbacksReturnCode feedbacks_api_update_feedback(const enum FeedbacksType type, const voltage value);

/*!
 * \brief Get the a feedback voltage voltage.
 * \param[in] type The type of the feedback to update return.
 * \param[out] value A pointer pointing to a variable where the result is written.
 * \retval FEEDBACKS_RC_OK on success.
 * \retval FEEDBACKS_RC_INVALID_TYPE if the type does not exist.
 * \retval FEEDBACKS_RC_NULL_POINTER if value is null.
 */
enum FeedbacksReturnCode lines_api_get_feedback(const enum FeedbacksType type, voltage *value);

/*!
 * \brief Get the a feedback voltage voltage.
 * \param[out] size Number of elements in the array.
 * \note The value pointed by the size pointer won't be updated in case of null pointer
 * \return The autonomous system line voltage in V.
 */
const voltage *feedbacks_api_get_feedbacks(size_t *size);
