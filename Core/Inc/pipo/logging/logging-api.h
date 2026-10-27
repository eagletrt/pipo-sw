#ifndef LOGGING_API_H
#define LOGGING_API_H
#include "logging.h"
#include "common.h"
enum LoggingReturnCode logging_api_init(logging_log log);
void logging_api_print_voltages(const voltage *volts, size_t size);
#endif // !LOGGING_API_H
