/*!
 * \file post-api.h
 * \author Riccardo Segala
 * \date 2026-06-1
 * \brief This module provides the APIs for the acquisition module
 */

#ifndef ACQUISITION_API_H
#define ACQUISITION_API_H

#include "acquisition.h"
#include <stddef.h>

/*!
 * \brief Initializes the acquisition module.
 *
 * This function initializes the acquisition subsystem and registers
 * the hardware-dependent callbacks required to start ADC conversions
 * and update the external multiplexer address. It should be called
 * once during system startup before any acquisition operations are
 * performed.
 *
 * \param[in] read_voltages Callback used to start an ADC acquisition.
 * \param[in] set_mux_address Callback used to update the mux address.
 *
 * \retval ACQUISITION_RC_OK on successful initialization.
 * \retval ACQUISITION_RC_NULL_POINTER if a callback argument is null.
 */
enum AcquisitionReturnCode acquisition_api_init(
    const acquisition_start_callback read_voltages,
    const acquisition_mux_address_callback set_mux_address);

/*!
 * \brief Processes newly acquired ADC samples.
 *
 * This function processes a block of raw ADC data received from the
 * acquisition hardware. The provided samples are incorporated into the
 * acquisition pipeline, allowing filtering, oversampling, and channel
 * updates to be performed.
 *
 * \param[in] data Pointer to the acquired ADC samples.
 * \param[in] length Number of samples to process.
 * \param[in] offset Starting index within the acquisition buffer.
 *
 * \retval ACQUISITION_RC_OK on successful processing.
 * \retval ACQUISITION_RC_NULL_POINTER if \p data is null.
 * \retval ACQUISITION_RC_OUT_OF_BOUNDS if the specified range exceeds
 *         the valid acquisition buffer bounds.
 */
enum AcquisitionReturnCode acquisition_api_handle_data(
    const voltage_raw *data,
    const size_t length);

#endif
