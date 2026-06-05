
#include "acquisition-api.h"
#include "eagletrt.h"
#include "tasks.h"

#include <string.h>

#define FILTER_ALPHA 0.5f
#define WARMUP_SAMPLES 20U
#define ADC12_TO_VOLTAGE(adc) ((float)(adc) * (3.3f / 4095.0f))
#define MUX_MAX_ADDRESS 16U

EAGLETRT_STATIC struct AcquisitionHandler handler;

EAGLETRT_STATIC_INLINE float prv_update_ema(float old, float new_sample) {
    return old + FILTER_ALPHA * (new_sample - old);
}

EAGLETRT_STATIC void prv_update_data_callback() {

    if (handler.sample_count[0] >= WARMUP_SAMPLES && handler.sample_count[1] >= WARMUP_SAMPLES) {
        handler.mux_address = (handler.mux_address + 1) % MUX_MAX_ADDRESS;
        handler.set_mux_address(handler.mux_address);
    }

    for (size_t i = 0; i < ACQUISITION_CHANNELS; i++) {

        if (handler.sample_count[i] >= WARMUP_SAMPLES) {

            // write data to db

            handler.sample_count[i] = 0;
        }
    }
}

struct TasksTask update_data_task __attribute__((section(".tasks"), aligned(sizeof(void *)))) = {
    .start_delay = 0,
    .period = 100,
    .last_execution = 0,
    .callback = prv_update_data_callback,
};

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
    const size_t length,
    const size_t offset) {

    if (data == nullptr) {
        return ACQUISITION_RC_NULL_POINTER;
    }

    if (length + offset >= ACQUISITION_CHANNELS) {
        return ACQUISITION_RC_OUT_OF_BOUNDS;
    }

    for (size_t i = offset; i < offset + length; i++) {
        if (handler.sample_count[i] < WARMUP_SAMPLES) {
            float x = ADC12_TO_VOLTAGE(data[i]);

            if (handler.sample_count[i] == 0) {
                handler.acquired_data[i] = x; // initialize
            } else {
                handler.acquired_data[i] =
                    prv_update_ema(handler.acquired_data[i], x);
            }

            handler.sample_count[i]++;
        }
    }

    return ACQUISITION_RC_OK;
}
