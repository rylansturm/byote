#ifndef BYOTE_H
#define BYOTE_H

typedef struct gap_buffer
{
    char* text;
    int   buffer_size;
    int   length;
    int   gap_index;
    int   gap_size;
} gap_buffer_t;

gap_buffer_t* byote_create_buffer(int size);
void          byote_free_buffer(gap_buffer_t* buffer);

void byote_load_buffer(gap_buffer_t* buffer,
                       const char*   file,
                       int           size);

void byote_split_buffer(gap_buffer_t* buffer, int index);
void byote_insert_char(gap_buffer_t* buffer,
                       int           index,
                       char          character);

void byote_print_full_buffer(gap_buffer_t* buffer);
void byote_print_buffer_text(gap_buffer_t* buffer);

#endif
