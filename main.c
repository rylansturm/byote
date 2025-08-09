#include "byote.h"
#include <stdio.h>

int main()
{
    gap_buffer_t* buffer = byote_create_buffer(20);
    byote_load_buffer(buffer, "Hello, World!", 13);
    byote_print_full_buffer(buffer);
    printf("\n");
    byote_print_buffer_text(buffer);
    printf("\n\n");

    byote_insert_char(buffer, 4, 'n');
    byote_print_full_buffer(buffer);
    printf("\n");
    byote_print_buffer_text(buffer);
    printf("\n\n");
    byote_free_buffer(buffer);

    buffer           = byote_create_buffer(64);
    char test_text[] = "7 * 6 = 42";

    byote_load_buffer(buffer, test_text, 10);

    // Insert a '0' after the '6'
    byote_insert_char(buffer, 5, '0');
    // Insert a '!' before the '='
    byote_insert_char(buffer, 7, '!');
    byote_print_buffer_text(buffer);
    byote_free_buffer(buffer);

    return 0;
}
