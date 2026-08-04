/*!
 * \file acquisition.h
 * \author Riccardo Segala
 * \date 2026-06-02
 * \brief Module for ADC acquisition and signal sampling
 */
#ifndef ACQUISITION_H
#define ACQUISITION_H

#include "common.h"
#include "lines.h"
#include "feedback.h"

#include <stdint.h>

/*! \brief Total number of physical ADC channels managed by the acquisition module */
#define ACQUISITION_CHANNELS 10U

#define MUX_MAX_ADDRESS 16U

#define ADC12_TO_VOLTAGE(adc) ((float)(adc) * (3.3f / 4095.0f))

#define VOLTAGE_FROM_DIVIDER(vout, r1, r2) \
    ((vout) * (((r1) + (r2)) / (r2)))

#define CURRENT_FROM_VOLTAGE_5A(voltage) \
    voltage / 800.0f * 1000.0f

#define CURRENT_FROM_VOLTAGE_20A(voltage) \
    voltage / 200.0f * 1000.0f

typedef uint16_t voltage_raw; /*!< Raw ADC count as returned by the hardware */
typedef uint8_t mux_address;  /*!< Multiplexer address index */

/*! \brief Callback to trigger a new ADC acquisition burst */
typedef void (*acquisition_start_callback)();

/*! \brief Callback to set the active multiplexer address */
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
 * \brief Destination module for an acquired channel value.
 *
 * Determines which module the value is forwarded to on publish.
 */
enum AcquisitionDestinationType {
    ACQUISITION_DESTINATION_TYPE_LINE_VOLTAGE,     /*!< Power line voltage, forwarded to the lines module */
    ACQUISITION_DESTINATION_TYPE_LINE_CURRENT_5A,  /*!< Power line current 5A, forwarded to the lines module */
    ACQUISITION_DESTINATION_TYPE_LINE_CURRENT_20A, /*!< Power line current 20A, forwarded to the lines module */
    ACQUISITION_DESTINATION_TYPE_FEEDBACK_5V,      /*!< 5V feedback signal, forwarded to the feedbacks module */
    ACQUISITION_DESTINATION_TYPE_FEEDBACK_24V,     /*!< 24V feedback signal, forwarded to the feedbacks module */
};

/*!
 * \brief Multiplexer identity for a channel.
 *
 * Indicates which physical mux drives the channel, or NONE for direct ADC channels.
 */
enum AcquisitionMuxType {
    ACQUISITION_MUX_TYPE_1,    /*!< Channel is driven by multiplexer 1 (line voltages) */
    ACQUISITION_MUX_TYPE_2,    /*!< Channel is driven by multiplexer 2 (line currents / last address feedback) */
    ACQUISITION_MUX_TYPE_NONE, /*!< Channel is a direct ADC input, not multiplexed */
};

/*!
 * \brief Resolved destination for a single acquired value.
 *
 * Pairs the destination module type with the specific index within that module.
 */
struct AcquisitionDestination {
    enum AcquisitionDestinationType type; /*!< Which module to forward the value to */
    union {
        enum FeedbacksType feedback; /*!< Target feedback index, used when type is FEEDBACK */
        enum LinesIndex line;        /*!< Target line index, used when type is LINE_VOLTAGE or LINE_CURRENT */
    } index;                         /*!< Destination index within the target module */
};

/*!
 * \brief Static descriptor for a single physical ADC channel.
 *
 * Encodes whether the channel is multiplexed and where its value is published
 * on oversample completion. One entry per physical channel in the channel map.
 */
struct AcquisitionChannel {
    enum AcquisitionMuxType mux;               /*!< Mux assignment for this channel */
    struct AcquisitionDestination destination; /*!< Publish destination module and index */
};

/*!
 * \brief Internal state of the acquisition module.
 *
 * Stores acquisition callbacks, filtered channel data,
 * sample counters, and multiplexer state.
 */
struct AcquisitionHandler {
    acquisition_start_callback read_voltages;         /*!< ADC acquisition callback */
    acquisition_mux_address_callback set_mux_address; /*!< Mux address setter callback */
    voltage acquired_data[ACQUISITION_CHANNELS];      /*!< Oversampled channel voltages in V */
    uint32_t sample_count[ACQUISITION_CHANNELS];      /*!< Number of samples accumulated per channel */
    mux_address mux_address;                          /*!< Mux address to be applied at the next acquisition cycle */
};

#endif /* ACQUISITION_H */
