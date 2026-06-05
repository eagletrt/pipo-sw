/*!
 * \file acquisition.h
 * \author Riccardo Segala
 * \date 2026-06-02
 * \brief Module for ADC acquisition and signal sampling
 */

#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <stdint.h>

#define ACQUISITION_CHANNELS 10U

typedef uint32_t voltage_raw;
typedef float voltage;
typedef uint8_t mux_address;

typedef void (*acquisition_start_callback)();
typedef void (*acquisition_mux_address_callback)(mux_address address);

/*!
 * \brief Return codes for the acquisition module APIs.
 */
enum AcquisitionReturnCode {
    ACQUISITION_RC_OK,            /*!< Operation completed successfully */
    ACQUISITION_RC_NULL_POINTER,  /*!< A pointer argument was null */
    ACQUISITION_RC_OUT_OF_BOUNDS, /*!< Index is outside valid range */
    ACQUISITION_RC_ERROR          /*!< Generic failure */
};

/*!
 * \brief Internal state of the acquisition module.
 *
 * Stores acquisition callbacks, filtered channel data,
 * sample counters, and multiplexer state.
 */
struct AcquisitionHandler {

    acquisition_start_callback read_voltages;         /*!< ADC acquisition callback */
    acquisition_mux_address_callback set_mux_address; /*!< Mux address callback */

    voltage acquired_data[ACQUISITION_CHANNELS]; /*!< Acquired channel voltages in V */
    uint32_t sample_count[ACQUISITION_CHANNELS]; /*!< Sample count per channel */

    mux_address mux_address; /*!< Current mux address */
};

#endif /* ACQUISITION_H */
