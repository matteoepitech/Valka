/*
** VALKA PROJECT, 2025
** src/core/prepass/prepass
** File description:
** File for handling the pre-pass which is needed for changing the definitions
*/

#include "valka.h"

/**
 * @brief Check if character is part of a word (alphanumeric or underscore).
 */
static bool_t
is_word_char(char c)
{
    return isalnum(c) || c == '_';
}

/**
 * @brief Check if a definition match is a complete word
 *        (not part of another word).
 */
static bool_t
is_complete_word_match(const char *buffer, size_t buffer_size, size_t pos,
    size_t def_len)
{
    if (pos > 0 && is_word_char(buffer[pos - 1]))
        return FALSE;
    if (pos + def_len < buffer_size && is_word_char(buffer[pos + def_len]))
        return FALSE;
    return TRUE;
}

/**
 * @brief Find matching definition at current position.
 */
static int32_t
find_definition_match(parsing_src_file_t *p, size_t pos)
{
    size_t def_len = 0;

    for (uint32_t i = 0; i < definitions_count; i++) {
        if (definitions_src[i]._def == NULL)
            continue; 
        def_len = strlen(definitions_src[i]._def);
        if (pos + def_len > p->_buffer_size)
            continue;
        if (strncmp(&p->_buffer[pos], definitions_src[i]._def, def_len) != 0)
            continue;
        if (!is_complete_word_match(p->_buffer, p->_buffer_size, pos, def_len))
            continue;
        return i;
    }
    return -1;
}

/**
 * @brief Ensure buffer has enough capacity and resize if needed.
 */
static void
ensure_buffer_capacity(char **buffer, size_t *capacity, size_t required_size)
{
    while (required_size >= *capacity) {
        *capacity *= 2;
        *buffer = REALLOC(*buffer, *capacity);
    }
}

/**
 * @brief Copy replacement value to new buffer.
 */
static void
copy_replacement(char **new_buffer, size_t *new_buffer_size, size_t *new_index, 
    const char *replacement)
{
    size_t val_len = strlen(replacement);

    ensure_buffer_capacity(new_buffer, new_buffer_size, *new_index + val_len);
    strcpy(&(*new_buffer)[*new_index], replacement);
    *new_index += val_len;
}

/**
 * @brief Copy single character to new buffer.
 */
static void
copy_character(char **new_buffer, size_t *new_buffer_size, size_t *new_index,
    char c)
{
    ensure_buffer_capacity(new_buffer, new_buffer_size, *new_index + 1);
    (*new_buffer)[*new_index] = c;
    (*new_index)++;
}

/**
 * @brief Replace definitions in the buffer.
 *
 * @param p The parsing structure
 */
void
replace_definitions(parsing_src_file_t *p)
{
    size_t new_buffer_size = p->_buffer_size * 2;
    char *new_buffer = MALLOC(new_buffer_size);
    size_t new_index = 0;
    size_t old_index = 0;
    int32_t def_match = 0;

    while (old_index < p->_buffer_size) {
        def_match = find_definition_match(p, old_index); 
        if (def_match >= 0 && definitions_src[def_match]._val) {
            copy_replacement(&new_buffer, &new_buffer_size, &new_index, 
                definitions_src[def_match]._val);
            old_index += strlen(definitions_src[def_match]._def);
        } else {
            copy_character(&new_buffer, &new_buffer_size, &new_index, 
                p->_buffer[old_index]);
            old_index++;
        }
    }
    p->_buffer = new_buffer;
    p->_buffer_size = new_index;
    p->_current_index = 0;
}
