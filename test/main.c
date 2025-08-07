#include "byote.h"
#include <check.h>

START_TEST(test_create_buffer)
{
    gap_buffer_t* buf = byote_create_buffer(64);
    ck_assert_ptr_nonnull(buf);
    ck_assert_int_eq(buf->gap_size, 64);
    ck_assert_int_eq(buf->gap_index, 0);
    ck_assert_int_eq(buf->length, 0);
    byote_free_buffer(buf);
}
END_TEST

Suite* byote_suite(void)
{
    Suite* s;
    TCase* tc_core;

    s       = suite_create("Byote");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_create_buffer);
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
