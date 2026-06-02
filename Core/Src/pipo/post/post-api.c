/*!
 * \file post-api.c
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief Implementation of the post module APIs
 */

#include "post-api.h"
#include "status-api.h"
#include "eagletrt-api.h"

static enum PostReturnCode prv_post_module_init(const struct PostInitData *data) {

    EAGLETRT_API_UNUSED(status_init(data->led_write));

    return POST_RC_OK;
}

enum PostReturnCode post_run(const struct PostInitData *data) {

    if (data->led_write == nullptr)
        return POST_RC_ERROR;

    return prv_post_module_init(data);
}
