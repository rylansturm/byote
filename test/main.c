#include "byote.h"
#include <check.h>
#include <stdio.h>

START_TEST(test_create_buffer)
{
    gap_buffer_t* buffer = byote_create_buffer(64);
    ck_assert_ptr_nonnull(buffer);
    ck_assert_int_eq(buffer->gap_size, 64);
    ck_assert_int_eq(buffer->gap_index, 0);
    ck_assert_int_eq(buffer->length, 0);
    for (int i = 0; i < 64; i++) {
        ck_assert_int_eq(buffer->text[i], 0);
    }
    byote_free_buffer(buffer);
}
END_TEST

START_TEST(test_load_buffer)
{
    gap_buffer_t* buffer      = byote_create_buffer(64);
    char          test_text[] = "Hello, World!";

    byote_load_buffer(buffer, test_text, 14);
    ck_assert_int_eq(buffer->length, 14);
    ck_assert_int_eq(buffer->gap_index, 14);
    ck_assert_int_eq(buffer->gap_size, 50);
    for (int i = 0; i < 14; i++) {
        ck_assert_int_eq(buffer->text[i], test_text[i]);
    }
    test_text[0] = 'F';
    ck_assert_int_eq(buffer->text[0], 'H');
    byote_free_buffer(buffer);
}
END_TEST

START_TEST(test_insert_buffer)
{
    gap_buffer_t* buffer      = byote_create_buffer(64);
    char          test_text[] = "7 * 6 = 42";

    byote_load_buffer(buffer, test_text, 10);

    // Insert a '0' after the '6'
    byote_insert_char(buffer, 5, '0');
    // Insert a '!' before the '='
    byote_insert_char(buffer, 7, '!');

    char former_expect_text[] = "7 * 60 !";
    char latter_expect_text[] = "= 42";

    for (int i = 0; i < 8; i++) {
        ck_assert_int_eq(buffer->text[i], former_expect_text[i]);
    }
    for (int i = 0; i < 4; i++) {
        int buf_index = buffer->gap_index + buffer->gap_size + i;
        ck_assert_int_eq(buffer->text[buf_index],
                         latter_expect_text[i]);
    }
}

Suite* byote_suite(void)
{
    Suite* s;
    TCase* tc_core;

    s       = suite_create("Byote");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_create_buffer);
    tcase_add_test(tc_core, test_load_buffer);
    tcase_add_test(tc_core, test_insert_buffer);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int      number_failed;
    Suite*   s;
    SRunner* sr;
    s  = byote_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}
