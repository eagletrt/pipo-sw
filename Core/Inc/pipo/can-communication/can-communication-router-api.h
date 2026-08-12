/*!
 * \file can-communication-router-api.h
 * \date 2026-08-09
 * \author Antonio Gelain [antonio.gelain2@gmail.com]
 *
 * \brief Generic API interface for routing abstracted CAN frames via PAL.
 */

#ifndef CAN_COMMUNICATION_ROUTER_API_H
#define CAN_COMMUNICATION_ROUTER_API_H

#include "can-communication.h"

/*!
 * \brief Function for incoming CAN frames on primary network.
 * \param[in] frame The frame just removed from the RX queue.
 * \retval CAN_COMMUNICATION_RC_OK on success.
 * \retval CAN_COMMUNICATION_RC_RECEIVE_HANDLER_ERROR if dispatch fails.
 */
enum CanCommunicationReturnCode can_communication_router_api_receive_primary(struct CanCommunicationFrame *frame);

#endif // CAN_COMMUNICATION_ROUTER_API_H
