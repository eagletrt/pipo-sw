
#include "acquisition-api.h"
#include "acquisition.h"
#include "eagletrt.h"
#include "feedbacks.h"
#include "task-api.h"

#include "lines-api.h"
#include "feedbacks-api.h"

#include <string.h>

#define ADC12_TO_VOLTAGE(adc) ((float)(adc) * (3.3f / 4095.0f))
#define MUX_MAX_ADDRESS 16U

EAGLETRT_STATIC struct AcquisitionHandler handler;

static const struct AcquisitionDestination mux2_map[] = {

    [0] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_LVBAT,
    },

    [1] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_COOL_LT,
    },

    [2] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_COOL_HT,
    },

    [3] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_HP_SPARE,
    },

    [4] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_VISION,
    },

    [5] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_PC,
    },

    [6] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_AS_EBS,
    },

    [7] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_AS_STEER,
    },

    [8] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_SD,
    },

    [9] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_LP_SPARE1,
    },

    [10] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_LP_SPARE2,
    },

    [11] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_DRIVER,
    },

    [12] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_LIGHTS,
    },

    [13] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_PWRTRAIN,
    },

    [14] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_TLM,
    },

    [15] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
        .index.line = LINES_INDEX_LP_MAIN,
    },
};

static const struct AcquisitionDestination mux1_map[] = {

    [0] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_LVBAT,
    },

    [1] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_COOL_LT,
    },

    [2] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_COOL_HT,
    },

    [3] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_HP_SPARE,
    },

    [4] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_VISION,
    },

    [5] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_PC,
    },

    [6] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_AS_EBS,
    },

    [7] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_AS_STEER,
    },

    [8] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_SD,
    },

    [9] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_LP_SPARE1,
    },

    [10] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_LP_SPARE2,
    },

    [11] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_DRIVER,
    },

    [12] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_LIGHTS,
    },

    [13] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_PWRTRAIN,
    },

    [14] = {
        .type = ACQUISITION_DESTINATION_TYPE_LINE_CURRENT,
        .index.line = LINES_INDEX_TLM,
    },

    [15] = {
        .type = ACQUISITION_DESTINATION_TYPE_FEEDBACK,
        .index.feedback = FEEDBACK_TYPE_5V,
    },
};

// clang-format off
static const struct AcquisitionChannel channels_map[] = {

    [0] = { .mux = ACQUISITION_MUX_TYPE_1 },

    [1] = { .mux = ACQUISITION_MUX_TYPE_2 },

    [2] = {
        .mux = ACQUISITION_MUX_TYPE_NONE,
        .destination = {
            .type = ACQUISITION_DESTINATION_TYPE_FEEDBACK,
            .index.feedback = FEEDBACK_TYPE_SHUTDOWN_OUT,
        } 
    },

    [3] = {
        .mux = ACQUISITION_MUX_TYPE_NONE,
        .destination = {
            .type = ACQUISITION_DESTINATION_TYPE_FEEDBACK,
            .index.feedback = FEEDBACK_TYPE_ASMS,
        }
    },

    [4] = {
        .mux = ACQUISITION_MUX_TYPE_NONE,
        .destination = {
            .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
            .index.line = LINES_INDEX_AS_MAIN,
        }
    },

    [5] = {
        .mux = ACQUISITION_MUX_TYPE_NONE,
        .destination = {
            .type = ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,
            .index.line = LINES_INDEX_HP_MAIN,
        }
    },

    [6] = {
        .mux = ACQUISITION_MUX_TYPE_NONE,
        .destination = {
            .type = ACQUISITION_DESTINATION_TYPE_FEEDBACK,
            .index.feedback = FEEDBACK_TYPE_RES_GO,
        }
    },

    [7] = {
        .mux = ACQUISITION_MUX_TYPE_NONE,
        .destination = {
            .type = ACQUISITION_DESTINATION_TYPE_FEEDBACK,
            .index.feedback = FEEDBACK_TYPE_SHUTDOWN_HVD,
        }
    },

    [8] = {
        .mux = ACQUISITION_MUX_TYPE_NONE,
        .destination = {
            .type = ACQUISITION_DESTINATION_TYPE_FEEDBACK,
            .index.feedback = FEEDBACK_TYPE_SHUTDOWN_BSPD,
        }
    },

    [9] = {
        .mux = ACQUISITION_MUX_TYPE_NONE,
        .destination = {
            .type = ACQUISITION_DESTINATION_TYPE_FEEDBACK,
            .index.feedback = FEEDBACK_TYPE_SHUTDOWN_TSMS,
        }
    },

};
// clang-format on

// #include <math.h>

// void float_to_string(float num, char *str, int precision) {
//     int int_part = (int)num;
//     float frac_part = fabsf(num - (float)int_part);

//     // handle negative numbers
//     if (num < 0 && int_part == 0) {
//         *str++ = '-';
//     }

//     // convert integer part
//     char temp[20];
//     int i = 0;

//     int n = int_part < 0 ? -int_part : int_part;

//     do {
//         temp[i++] = (n % 10) + '0';
//         n /= 10;
//     } while (n > 0);

//     // reverse integer digits into output
//     while (i--) {
//         *str++ = temp[i];
//     }

//     *str++ = '.';

//     // convert fractional part
//     for (int j = 0; j < precision; j++) {
//         frac_part *= 10;
//         int digit = (int)frac_part;
//         *str++ = digit + '0';
//         frac_part -= digit;
//     }

//     *str = '\0';
// }

// void print_float(float data) {
//     char str[100];

//     float_to_string(data, str, 2);

//     usart_log(str);
//     usart_log(" ");
// }

// void print_data() {

//     const voltage *data;
//     size_t size;

//     // data = feedbacks_api_get_feedbacks(&size);
//     data = lines_api_get_line_voltages(&size);

//     for (size_t i = 0; i < size; i++) {
//         print_float(data[i]);
//     }
//     usart_log("\r\n");
// }
//
// struct Task print_data_task __attribute__((section(".tasks"), aligned(sizeof(void *)))) = {
//     .start_delay = 0,
//     .period = 1000,
//     .last_execution = 0,
//     .callback = print_data,
// };

EAGLETRT_STATIC enum AcquisitionReturnCode prv_publish_data(const struct AcquisitionDestination destination, voltage value) {

    switch (destination.type) {
        case ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE:
            lines_api_update_line_voltage(destination.index.line, value);
            break;
        case ACQUISITION_DESTINATION_TYPE_LINE_CURRENT:
            lines_api_update_line_current(destination.index.line, value);
            break;
        case ACQUISITION_DESTINATION_TYPE_FEEDBACK:
            feedbacks_api_update_feedback(destination.index.feedback, value);
            break;
    }

    return ACQUISITION_RC_OK;
}

EAGLETRT_STATIC void prv_update_data_callback() {
    handler.mux_address = (handler.mux_address + 1) % MUX_MAX_ADDRESS;
    handler.set_mux_address(handler.mux_address);
    handler.read_voltages();
}

TASK_API_REGISTER(update_data_task, 0, 100, prv_update_data_callback);

enum AcquisitionReturnCode acquisition_api_init(
    const acquisition_start_callback read_voltages,
    const acquisition_mux_address_callback set_mux_address) {

    if (read_voltages == nullptr || set_mux_address == nullptr)
        return ACQUISITION_RC_NULL_POINTER;

    memset(&handler, 0, sizeof(handler));

    handler.read_voltages = read_voltages;
    handler.set_mux_address = set_mux_address;

    return ACQUISITION_RC_OK;
}

enum AcquisitionReturnCode acquisition_api_handle_data(
    const voltage_raw *data,
    const size_t length) {

    if (data == nullptr) {
        return ACQUISITION_RC_NULL_POINTER;
    }

    if (length >= ACQUISITION_CHANNELS) {
        return ACQUISITION_RC_OUT_OF_BOUNDS;
    }

    for (size_t i = 0; i < length; i++) {

        float x = ADC12_TO_VOLTAGE(data[i]);

        switch (channels_map[i].mux) {
            case ACQUISITION_MUX_TYPE_1:
                prv_publish_data(mux1_map[handler.mux_address], x);
                break;

            case ACQUISITION_MUX_TYPE_2:
                prv_publish_data(mux2_map[handler.mux_address], x);
                break;

            case ACQUISITION_MUX_TYPE_NONE:
                prv_publish_data(channels_map[i].destination, x);
                break;
        }
    }
    return ACQUISITION_RC_OK;
}
