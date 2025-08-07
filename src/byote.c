#include "byote.h"
#include <stdlib.h>
#include <string.h>

gap_buffer_t* byote_create_buffer(int size)
{
    gap_buffer_t* buffer = malloc(sizeof(gap_buffer_t));
    if (!buffer) {
        return NULL;
    }

    buffer->text = malloc(size * sizeof(char));
    if (!buffer->text) {
        free(buffer);
        return NULL;
    }
    buffer->gap_index   = 0;
    buffer->gap_size    = size;
    buffer->buffer_size = size;
    buffer->length      = 0;

    memset(buffer->text, 0, size);

    return buffer;
}

void byote_free_buffer(gap_buffer_t* buffer)
{
    if (buffer) {
        free(buffer->text);
        free(buffer);
    }
}

void byote_load_buffer(gap_buffer_t* buffer,
                       const char*   text,
                       int           size)
{
    if (!buffer || !text || size < 0) {
        return;
    }
    if (size > buffer->buffer_size) {
        size = buffer->buffer_size;
    }

    memcpy(buffer->text, text, size);
    buffer->gap_index = size;
    buffer->gap_size  = buffer->buffer_size - size;
    buffer->length    = size;
}

void byote_split_buffer(gap_buffer_t* buffer, int index)
{
    if (!buffer || index < 0 || index > buffer->length) {
        return;
    }
    if (index < buffer->gap_index) {
        while (buffer->gap_index > index) {
            int new_index = buffer->gap_index + buffer->gap_size - 1;
            int old_index = buffer->gap_index - 1;
            buffer->text[new_index] = buffer->text[old_index];
            buffer->gap_index--;
        }
    } else if (index > buffer->gap_index) {
        while (buffer->gap_index < index) {
            int new_index = buffer->gap_index;
            int old_index = buffer->gap_index + buffer->gap_size;
            buffer->text[new_index] = buffer->text[old_index];
            buffer->gap_index++;
        }
    }
}

void byote_insert_char(gap_buffer_t* buffer,
                       int           index,
                       char          character)
{
    if (!buffer || index < 0 || index > buffer->length ||
        buffer->gap_size <= 0) {
        return;
    }
    if (index != buffer->gap_index) {
        byote_split_buffer(buffer, index);
    }
    buffer->text[buffer->gap_index] = character;
    buffer->gap_index++;
    buffer->gap_size--;
    buffer->length++;
}
