/*!
 * \file lines.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief Module for managing the output power lines
 */

#ifndef LINES_H
#define LINES_H

#define LINES_NUM_LINES 14

typedef float voltage;
typedef float current;

/*!
 * \brief Return codes for the lines module APIs.
 */
enum LinesReturnCode {
    LINES_RC_OK,            /*!< Operation completed successfully */
    LINES_RC_OUT_OF_BOUNDS, /*!< Could not write or read a value because the index was invalid*/
    LINES_RC_,              /*!<  */
    LINES_RC_ERROR,         /*!< Operation not completed */
};

/*!
 * \brief Return codes for the lines module APIs.
 */
enum LinesIndex {
    LINES_INDEX_PALLE = 0x00, /*!< The index for the PALLE line */
};

/*!
 * \brief Internal state of the lines module.
 */
struct LinesHandler {
    current lines_current[LINES_NUM_LINES]; /*!< Each line current in A */
    voltage lines_voltage[LINES_NUM_LINES]; /*!< Each line voltage in V */
    voltage high_power_voltage;             /*!< The high power line voltage in V */
    voltage low_power_voltage;              /*!< The low power line voltage in V */
};

#endif
