/*!
 * \file post-api.c
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief Implementation of the post module APIs
 */

#include "post-api.h"
#include "can-communication-api.h"
#include "can-communication.h"
#include "post.h"
#include "status-api.h"
#include "acquisition-api.h"

#include "eagletrt-api.h"

EAGLETRT_STATIC enum PostReturnCode prv_post_module_init(const struct PostInitData *data) {
    enum PostReturnCode return_code = POST_RC_OK;
    if (can_communication_api_init(data->can_networks) != CAN_COMMUNICATION_RC_OK) {
        return_code = POST_RC_ERROR;
    }
    EAGLETRT_API_UNUSED(status_api_init(data->led_write));
    EAGLETRT_API_UNUSED(acquisition_api_init(data->read_voltages, data->mux_set));
    return return_code;
}

enum PostReturnCode post_api_run(const struct PostInitData *data) {

    if (data->led_write == nullptr ||
        data->read_voltages == nullptr ||
        data->mux_set == nullptr)
        return POST_RC_ERROR;

    return prv_post_module_init(data);
}
