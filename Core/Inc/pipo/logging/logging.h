#ifndef LOGGING_H
#define LOGGING_H
typedef void (*logging_log)(const char *str);

struct LoggingHandler {
    logging_log log;
};

enum LoggingReturnCode {
    LOGGING_RC_NULL_POINTER,
    LOGGING_RC_OK
};
#endif // !LOGGING_H
