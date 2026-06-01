/*!
 * \file lines.h
 * \author Riccardo Segala 
 * \date 2026-06-1
 * \brief Module for managing the power lines
 */

#ifndef LINES_H
#define LINES_H

typedef float voltage;
typedef float current;

/*!
 * \brief Return codes for the lines module APIs.
 */
enum LinesReturnCode {
    LINES_RC_OK,            /*!< Operation completed successfully */
    LINES_RC_OUT_OF_BOUNDS, /*!< Index is outside valid range */
    LINES_RC_NULL_POINTER,  /*!< A pointer argument was null */
    LINES_RC_ERROR          /*!< Generic failure */
};

/*!
 * \brief Unified index map for all power and signal lines.
 *
 * This includes:
 * - Low voltage auxiliary rails (LP)
 * - High power rails (HP)
 * - Autonomous system supply (AS)
 * - General system loads
 */
enum LinesIndex {

    /* Low power domain */
    LINES_INDEX_LP_MAIN = 0x00, /*!< Low power spare 1 */
    LINES_INDEX_LP_SPARE1,      /*!< Low power spare 1 */
    LINES_INDEX_LP_SPARE2,      /*!< Low power spare 2 */
    LINES_INDEX_DRIVER,         /*!< Low power driver supply */
    LINES_INDEX_LIGHTS,         /*!< Low power lights supply */
    LINES_INDEX_PWRTRAIN,       /*!< Low power powertrain supply */
    LINES_INDEX_TLM,            /*!< Low power telemetry supply */
    LINES_INDEX_SD,             /*!< Shutdown circuit */
    LINES_INDEX_COOL_LT,        /*!< Low temperature cooling */
    LINES_INDEX_COOL_HT,        /*!< High temperature cooling */

    /* High power domain */
    LINES_INDEX_HP_MAIN,  /*!< High power main rail */
    LINES_INDEX_LVBAT,    /*!< Low voltage battery */
    LINES_INDEX_HP_SPARE, /*!< High power spare rail */
    LINES_INDEX_PC,       /*!< Precharge control */
    LINES_INDEX_VISION,   /*!< Low power spare 1 */

    /* Autonomous system domain */
    LINES_INDEX_AS_MAIN,  /*!< Autonomous system main supply */
    LINES_INDEX_AS_EBS,   /*!< Emergency brake system */
    LINES_INDEX_AS_STEER, /*!< Steering system */

    LINES_INDEX_COUNT /*!< Number of lines */
};

/*!
 * \brief Internal state of the lines module.
 *
 * All voltages and currents are indexed using LinesIndex.
 */
struct LinesHandler {
    current lines_current[LINES_INDEX_COUNT]; /*!< Line currents in A */
    voltage lines_voltage[LINES_INDEX_COUNT]; /*!< Line voltages in V */
};

#endif
