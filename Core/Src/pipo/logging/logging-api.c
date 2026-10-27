/*!
 * \file logging-api.c
 * \author Mario Mazzara
 * \date 2026-10-27
 * \brief Public API logging logging implementation.
 */
#include <math.h>
#include "logging-api.h"
#include "eagletrt.h"

EAGLETRT_STATIC struct LoggingHandler handler;

enum LoggingReturnCode logging_api_init(logging_log log) {
    if (log == NULL) {
        return LOGGING_RC_NULL_POINTER;
    }
    handler.log = log;
    return LOGGING_RC_OK;
}

void prv_float_to_string(float num, char *str, int precision) {
    int int_part = (int)num;
    float frac_part = fabsf(num - (float)int_part);

    // handle negative numbers
    if (num < 0 && int_part == 0) {
        *str++ = '-';
    }

    // convert integer part
    char temp[20];
    int i = 0;

    int n = int_part < 0 ? -int_part : int_part;

    do {
        temp[i++] = (n % 10) + '0';
        n /= 10;
    } while (n > 0);

    // reverse integer digits into output
    while (i--) {
        *str++ = temp[i];
    }

    *str++ = '.';

    // convert fractional part
    for (int j = 0; j < precision; j++) {
        frac_part *= 10;
        int digit = (int)frac_part;
        *str++ = digit + '0';
        frac_part -= digit;
    }

    *str = '\0';
}

void prv_print_float(float data) {
    char str[100];

    prv_float_to_string(data, str, 2);

    handler.log(str);
    handler.log(" ");
}

void logging_api_print_voltages(const voltage *volts, size_t size) {
    if (volts == NULL || handler.log == NULL)
        return;
    for (size_t i = 0; i < size; i++) {
        prv_print_float(volts[i]);
    }
    handler.log("\r\n");
}
