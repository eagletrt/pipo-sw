/*!
 * \file feedbacks-api.c
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief Implementation of the lines module APIs
 */

#include <string.h>

#include "can-primary-api.h"
#include "eagletrt-api.h"
#include "eagletrt.h"

#include "can-communication.h"
#include "can-communication-api.h"
#include "feedback.h"
#include "feedback-api.h"
#include "task-api.h"

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

EAGLETRT_STATIC void prv_feedback_can_routine(void) {
    struct CanCommunicationFrame frame = {
        .id = CAN_PRIMARY_MESSAGE_FRAME_ID_PIPOSHUTDOWN
    };

    struct CanPrimaryPiposhutdown *payload = &handler.libcan_message_shutdown.piposhutdown;
    payload->lvms = handler.feedbacks[FEEDBACK_TYPE_5V];
    payload->hvd = handler.feedbacks[FEEDBACK_TYPE_SHUTDOWN_HVD];
    payload->bspd = handler.feedbacks[FEEDBACK_TYPE_SHUTDOWN_BSPD];
    payload->asms = handler.feedbacks[FEEDBACK_TYPE_ASMS];
    payload->res = handler.feedbacks[FEEDBACK_TYPE_SHUTDOWN_OUT];
    payload->tsms = handler.feedbacks[FEEDBACK_TYPE_SHUTDOWN_TSMS];

    int byte_size = can_primary_api_serialize_from_id(
        frame.id,
        &handler.libcan_message_shutdown,
        frame.data);
    if (byte_size >= 0) {
        frame.length = byte_size;
        EAGLETRT_API_UNUSED(can_communication_api_add_to_tx(CAN_COMMUNICATION_NETWORK_PRIMARY, &frame));
    }
}

TASK_API_REGISTER(feedback_can_send_task, 5, can_primary_byte_size_piposhutdown, prv_feedback_can_routine);
