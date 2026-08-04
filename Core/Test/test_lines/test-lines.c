
/*!
 * \file test_lines.c
 * \author Riccardo Segala
 * \date 2026-06-18
 * \brief Unit tests using Unity for testing the lines module APIs
 *
 * \details This test suite verifies the correctness of the lines API,
 * including boundary checks, getter/setter behavior, and internal state
 * consistency via public interfaces.
 */

#include <unity.h>
#include <string.h>
#include <stdbool.h>

#include "lines-api.h"
#include "lines.h"

/* --- Test setup --- */

void setUp(void) {
    /* Reset module state before each test */
    lines_api_init();
}

void tearDown(void) {
    /* nothing */
}

/* --- Helpers --- */

static void fill_test_data(void) {
    for (int i = 0; i < LINES_INDEX_COUNT; i++) {
        lines_api_update_line_voltage((enum LinesIndex)i, (float)(i * 1.0f + 0.5f));
        lines_api_update_line_current((enum LinesIndex)i, (float)(i * 2.0f + 1.0f));
    }
}

/* --- Test group: init --- */

void test_lines_api_init_resets_state(void) {
    fill_test_data();

    enum LinesReturnCode rc = lines_api_init();
    TEST_ASSERT_EQUAL(LINES_RC_OK, rc);

    size_t size = 0;
    const voltage *v = lines_api_get_line_voltages(&size);

    TEST_ASSERT_EQUAL(LINES_INDEX_COUNT, size);

    for (int i = 0; i < LINES_INDEX_COUNT; i++) {
        TEST_ASSERT_EQUAL_FLOAT(0.0f, v[i]);
    }
}

/* --- Test group: update voltage --- */

void test_lines_api_update_voltage_success(void) {
    enum LinesReturnCode rc =
        lines_api_update_line_voltage(LINES_INDEX_LP_MAIN, 12.5f);

    TEST_ASSERT_EQUAL(LINES_RC_OK, rc);

    voltage value = 0.0f;
    lines_api_get_line_voltage(LINES_INDEX_LP_MAIN, &value);

    TEST_ASSERT_EQUAL_FLOAT(12.5f, value);
}

void test_lines_api_update_voltage_out_of_bounds(void) {
    enum LinesReturnCode rc =
        lines_api_update_line_voltage(LINES_INDEX_COUNT, 10.0f);

    TEST_ASSERT_EQUAL(LINES_RC_OUT_OF_BOUNDS, rc);
}

/* --- Test group: update current --- */

void test_lines_api_update_current_success(void) {
    enum LinesReturnCode rc =
        lines_api_update_line_current(LINES_INDEX_HP_MAIN, 3.3f);

    TEST_ASSERT_EQUAL(LINES_RC_OK, rc);

    current value = 0.0f;
    lines_api_get_line_current(LINES_INDEX_HP_MAIN, &value);

    TEST_ASSERT_EQUAL_FLOAT(3.3f, value);
}

void test_lines_api_update_current_out_of_bounds(void) {
    enum LinesReturnCode rc =
        lines_api_update_line_current(LINES_INDEX_COUNT, 1.0f);

    TEST_ASSERT_EQUAL(LINES_RC_OUT_OF_BOUNDS, rc);
}

/* --- Test group: get single voltage --- */

void test_lines_api_get_voltage_null_pointer(void) {
    enum LinesReturnCode rc =
        lines_api_get_line_voltage(LINES_INDEX_LP_MAIN, NULL);

    TEST_ASSERT_EQUAL(LINES_RC_NULL_POINTER, rc);
}

void test_lines_api_get_voltage_out_of_bounds(void) {
    voltage value = 0.0f;

    enum LinesReturnCode rc =
        lines_api_get_line_voltage(LINES_INDEX_COUNT, &value);

    TEST_ASSERT_EQUAL(LINES_RC_OUT_OF_BOUNDS, rc);
}

/* --- Test group: get single current --- */

void test_lines_api_get_current_null_pointer(void) {
    enum LinesReturnCode rc =
        lines_api_get_line_current(LINES_INDEX_LP_MAIN, NULL);

    TEST_ASSERT_EQUAL(LINES_RC_NULL_POINTER, rc);
}

void test_lines_api_get_current_out_of_bounds(void) {
    current value = 0.0f;

    enum LinesReturnCode rc =
        lines_api_get_line_current(LINES_INDEX_COUNT, &value);

    TEST_ASSERT_EQUAL(LINES_RC_OUT_OF_BOUNDS, rc);
}

/* --- Test group: bulk getters --- */

void test_lines_api_get_voltage_array_and_size(void) {
    fill_test_data();

    size_t size = 0;
    const voltage *v = lines_api_get_line_voltages(&size);

    TEST_ASSERT_NOT_NULL(v);
    TEST_ASSERT_EQUAL(LINES_INDEX_COUNT, size);

    for (int i = 0; i < LINES_INDEX_COUNT; i++) {
        TEST_ASSERT_EQUAL_FLOAT((float)(i * 1.0f + 0.5f), v[i]);
    }
}

void test_lines_api_get_current_array_and_size(void) {
    fill_test_data();

    size_t size = 0;
    const current *c = lines_api_get_line_currents(&size);

    TEST_ASSERT_NOT_NULL(c);
    TEST_ASSERT_EQUAL(LINES_INDEX_COUNT, size);

    for (int i = 0; i < LINES_INDEX_COUNT; i++) {
        TEST_ASSERT_EQUAL_FLOAT((float)(i * 2.0f + 1.0f), c[i]);
    }
}

/* --- Test group: mixed updates consistency --- */

void test_lines_api_voltage_current_independence(void) {
    lines_api_update_line_voltage(LINES_INDEX_LP_MAIN, 5.0f);
    lines_api_update_line_current(LINES_INDEX_LP_MAIN, 2.0f);

    voltage v = 0.0f;
    current c = 0.0f;

    lines_api_get_line_voltage(LINES_INDEX_LP_MAIN, &v);
    lines_api_get_line_current(LINES_INDEX_LP_MAIN, &c);

    TEST_ASSERT_EQUAL_FLOAT(5.0f, v);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, c);
}

/* --- main --- */

int main(void) {
    UNITY_BEGIN();

    /* init */
    RUN_TEST(test_lines_api_init_resets_state);

    /* voltage */
    RUN_TEST(test_lines_api_update_voltage_success);
    RUN_TEST(test_lines_api_update_voltage_out_of_bounds);
    RUN_TEST(test_lines_api_get_voltage_null_pointer);
    RUN_TEST(test_lines_api_get_voltage_out_of_bounds);

    /* current */
    RUN_TEST(test_lines_api_update_current_success);
    RUN_TEST(test_lines_api_update_current_out_of_bounds);
    RUN_TEST(test_lines_api_get_current_null_pointer);
    RUN_TEST(test_lines_api_get_current_out_of_bounds);

    /* bulk */
    RUN_TEST(test_lines_api_get_voltage_array_and_size);
    RUN_TEST(test_lines_api_get_current_array_and_size);

    /* consistency */
    RUN_TEST(test_lines_api_voltage_current_independence);

    return UNITY_END();
}
