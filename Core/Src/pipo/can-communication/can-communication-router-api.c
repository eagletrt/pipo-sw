/*!
 * \file can-communication-router-api.c
 * \date 2026-08-09
 * \author Antonio Gelain [antonio.gelain2@gmail.com]
 *
 * \brief Implementation of the CAN-bus communication module.
 */

#include "can-communication-router-api.h"

#include "can-communication.h"
#include "can-primary-api.h"
#include "can-primary.h"

enum CanCommunicationReturnCode can_communication_router_api_receive_primary(struct CanCommunicationFrame *frame) {
    if (frame == nullptr) {
        return CAN_COMMUNICATION_RC_NULL_POINTER;
    }

    if (!can_primary_api_id_is_valid(frame->id)) {
        return CAN_COMMUNICATION_RC_INVALID_NETWORK;
    }

    union CanPrimaryMessages message = { 0 };
    if (can_primary_api_deserialize_from_id(frame->id, frame->data, &message) != 0) {
        return CAN_COMMUNICATION_RC_ERROR;
    }

    switch (frame->id) {
        default:
            break;
    }

    return CAN_COMMUNICATION_RC_OK;
}
