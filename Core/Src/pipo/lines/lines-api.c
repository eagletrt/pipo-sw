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
    const size_t index,
    const voltage value) {

    if (index >= LINES_INDEX_COUNT) {
        return LINES_RC_OUT_OF_BOUNDS;
    }

    handler.lines_voltage[index] = value;

    return LINES_RC_OK;
}

enum LinesReturnCode lines_api_update_line_voltages(
    const size_t index,
    const voltage *values,
    const size_t size) {

    if (values == NULL) {
        return LINES_RC_ERROR;
    }

    if ((index + size) > LINES_INDEX_COUNT) {
        return LINES_RC_OUT_OF_BOUNDS;
    }

    memcpy(
        &handler.lines_voltage[index],
        values,
        size * sizeof(*values));

    return LINES_RC_OK;
}

enum LinesReturnCode lines_api_update_line_current(
    const size_t index,
    const current value) {

    if (index >= LINES_INDEX_COUNT) {
        return LINES_RC_OUT_OF_BOUNDS;
    }

    handler.lines_current[index] = value;

    return LINES_RC_OK;
}

enum LinesReturnCode lines_api_update_line_currents(
    const size_t index,
    const current *values,
    const size_t size) {

    if (values == NULL) {
        return LINES_RC_ERROR;
    }

    if ((index + size) > LINES_INDEX_COUNT) {
        return LINES_RC_OUT_OF_BOUNDS;
    }

    memcpy(
        &handler.lines_current[index],
        values,
        size * sizeof(*values));

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
    const size_t index,
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
    const size_t index,
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
