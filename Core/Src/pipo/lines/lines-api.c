/*!
 * \file lines-api.c
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief Implementation of the lines module APIs
 */

#include "lines-api.h"
#include "eagletrt.h"
#include <string.h>

EAGLETRT_STATIC struct LinesHandler handler;

enum LinesReturnCode lines_api_init(void) {
    memset(&handler, 0, sizeof(handler));

    return LINES_RC_OK;
}

enum LinesReturnCode lines_api_update_line_voltage(
    const enum LinesIndex index,
    const voltage value) {

    if (index >= LINES_INDEX_COUNT) {
        return LINES_RC_OUT_OF_BOUNDS;
    }

    handler.lines_voltage[index] = value;

    return LINES_RC_OK;
}

enum LinesReturnCode lines_api_update_line_current(
    const enum LinesIndex index,
    const current value) {

    if (index >= LINES_INDEX_COUNT) {
        return LINES_RC_OUT_OF_BOUNDS;
    }

    handler.lines_current[index] = value;

    return LINES_RC_OK;
}

const voltage *lines_api_get_line_voltages(size_t *size) {
    if (size != NULL) {
        *size = LINES_INDEX_COUNT;
    }

    return handler.lines_voltage;
}

const current *lines_api_get_line_currents(size_t *size) {
    if (size != NULL) {
        *size = LINES_INDEX_COUNT;
    }

    return handler.lines_current;
}

enum LinesReturnCode lines_api_get_line_voltage(
    const enum LinesIndex index,
    voltage *value) {

    if (value == NULL) {
        return LINES_RC_NULL_POINTER;
    }

    if (index >= LINES_INDEX_COUNT) {
        return LINES_RC_OUT_OF_BOUNDS;
    }

    *value = handler.lines_voltage[index];
    return LINES_RC_OK;
}

enum LinesReturnCode lines_api_get_line_current(
    const enum LinesIndex index,
    current *value) {

    if (value == NULL) {
        return LINES_RC_NULL_POINTER;
    }

    if (index >= LINES_INDEX_COUNT) {
        return LINES_RC_OUT_OF_BOUNDS;
    }

    *value = handler.lines_current[index];
    return LINES_RC_OK;
}
