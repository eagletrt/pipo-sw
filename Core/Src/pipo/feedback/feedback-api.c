/*!
 * \file feedbacks-api.c
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief Implementation of the lines module APIs
 */

#include "feedback.h"
#include "feedback-api.h"

#include <string.h>

/* Internal module state */
static struct FeedbacksHandler handler;

enum FeedbacksReturnCode feedbacks_api_init(void) {
    memset(&handler, 0, sizeof(handler));
    return FEEDBACKS_RC_OK;
}

enum FeedbacksReturnCode feedbacks_api_update_feedback(
    const enum FeedbacksType type,
    const voltage value) {

    if (type >= FEEDBACK_TYPE_COUNT) {
        return FEEDBACKS_RC_INVALID_TYPE;
    }

    handler.feedbacks[type] = value;

    return FEEDBACKS_RC_OK;
}

enum FeedbacksReturnCode feedbacks_api_get_feedback(
    const enum FeedbacksType type,
    voltage *value) {

    if (type >= FEEDBACK_TYPE_COUNT) {
        return FEEDBACKS_RC_INVALID_TYPE;
    }

    if (value == NULL) {
        return FEEDBACKS_RC_NULL_POINTER;
    }

    *value = handler.feedbacks[type];

    return FEEDBACKS_RC_OK;
}

const voltage *feedbacks_api_get_feedbacks(size_t *size) {
    if (size != NULL) {
        *size = FEEDBACK_TYPE_COUNT;
    }

    return handler.feedbacks;
}
