/*!
 * \file status-api.c
 * \author Riccardo Segala
 * \date 2026-06-2
 * \brief Implementation of the status module APIs
 */

#include "status-api.h"

#include <stddef.h>
#include <string.h>

#include "can-primary.h"
#include "can-primary-api.h"
#include "eagletrt.h"

#include "can-communication.h"
#include "can-communication-api.h"
#include "task-api.h"
#include "status.h"

#define ANIMATION_END 0xff
#define ANIMATION_MAX_LENGTH 16

EAGLETRT_STATIC const uint8_t animation_bitmaps[STATUS_TYPE_COUNT][ANIMATION_MAX_LENGTH] = {
    [STATUS_TYPE_IDLE] = { 0x00, 0x01, 0x02, 0x04, ANIMATION_END },
    [STATUS_TYPE_FLASH] = { 0x00, 0x05, 0x02, 0x05, ANIMATION_END },
    [STATUS_TYPE_FATAL] = { 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, 0x07, 0x07, 0x00, ANIMATION_END }
};

/* Internal module state */
EAGLETRT_STATIC struct StatusHandler handler;

enum StatusReturnCode status_api_init(status_led_write led_write) {

    if (led_write == NULL)
        return STATUS_RC_NULL_POINTER;

    memset(&handler, 0, sizeof(handler));

    handler.status = STATUS_TYPE_IDLE;
    handler.led_write = led_write;

    return STATUS_RC_OK;
}

enum StatusReturnCode status_api_set_status(enum StatusType status) {
    if (status >= STATUS_TYPE_COUNT) {
        return STATUS_RC_INVALID_TYPE;
    }

    handler.status = status;

    // Reset the animation
    handler.animation_index = 0;

    return STATUS_RC_OK;
}

EAGLETRT_STATIC void prv_status_routine(void) {
    if (animation_bitmaps[handler.status][handler.animation_index] == ANIMATION_END) {
        // If the animation is ended reset the animation index
        handler.animation_index = 0;
    }

    // Write the current animation frame bitmap
    handler.led_write(
        animation_bitmaps[handler.status][handler.animation_index++]);
}

EAGLETRT_STATIC void prv_status_can_routine(void) {
    struct CanCommunicationFrame frame = {
        .id = CAN_PRIMARY_MESSAGE_FRAME_ID_PIPOFSM
    };

    struct CanPrimaryPipofsm *payload = &handler.libcan_message_status.pipofsm;
    payload->status = handler.status;

    int byte_size = can_primary_api_serialize_from_id(
        frame.id,
        &handler.libcan_message_status,
        frame.data);
    if (byte_size >= 0) {
        frame.length = byte_size;
        EAGLETRT_API_UNUSED(can_communication_api_add_to_tx(CAN_COMMUNICATION_NETWORK_PRIMARY, &frame));
    }
}

TASK_API_REGISTER(status_task, 0, 200, prv_status_routine);
TASK_API_REGISTER(status_can_send_task, 5, can_primary_cycle_time_pipofsm, prv_status_can_routine);
