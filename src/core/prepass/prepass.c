/*
** VALKA PROJECT, 2025
** src/core/prepass/prepass
** File description:
** File for handling the pre-pass which is needed for changing the definitions
*/

#include "valka.h"

/**
 * @brief Skip whitespace characters.
 *
 * @param p             The parsing source struct
 */
static void
skip_whitespace(parsing_src_file_t *p)
{
    while (p->_current_index < p->_buffer_size && 
           isspace(p->_buffer[p->_current_index])) {
        p->_current_index++;
    }
}

/**
 * @brief Extract a word from the buffer.
 *
 * @param p             The parsing source struct
 *
 * @return The a word.
 */
static char *
extract_word(parsing_src_file_t *p)
{
    size_t start = 0;
    size_t len = 0;
    char *word = NULL;

    while (p->_current_index < p->_buffer_size && 
           !isalnum(p->_buffer[p->_current_index]) && 
           p->_buffer[p->_current_index] != '_') {
        p->_current_index++;
    }   
    start = p->_current_index;
    len = 0;
    while (p->_current_index < p->_buffer_size && 
           (isalnum(p->_buffer[p->_current_index]) || 
            p->_buffer[p->_current_index] == '_')) {
        p->_current_index++;
        len++;
    }
    if (len == 0)
        return NULL;     
    word = MALLOC(len + 1);
    strncpy(word, &p->_buffer[start], len);
    word[len] = '\0';
    return word;
}

/**
 * @brief Extract a value (can contain spaces and special characters).
 *
 * @param p             The parsing source struct
 *
 * @return The value.
 */
static char *
extract_value(parsing_src_file_t *p)
{
    char *value = NULL;
    size_t start = 0;
    size_t len = 0;

    skip_whitespace(p);
    start = p->_current_index;
    len = 0;
    while (p->_current_index < p->_buffer_size && 
           p->_buffer[p->_current_index] != '\n' &&
           p->_buffer[p->_current_index] != '\r') {
        p->_current_index++;
        len++;
    }
    if (len == 0)
        return NULL;
    while (len > 0 && isspace(p->_buffer[start + len - 1]))
        len--;
    if (len == 0)
        return NULL;
    value = MALLOC(len + 1);
    strncpy(value, &p->_buffer[start], len);
    value[len] = '\0';
    return value;
}

/**
 * @brief Parse a @def directive.
 *
 * @param p             The parsing source struct
 *
 * @return TRUE or FALSE.
 */
static bool_t
parse_def_directive(parsing_src_file_t *p)
{
    char *def_name = NULL;
    char *def_value = NULL;

    p->_current_index += 4;
    skip_whitespace(p);
    def_name = extract_word(p);
    if (def_name == NULL)
        return FALSE;    
    skip_whitespace(p);
    def_value = extract_value(p);
    if (def_value == NULL)
        return FALSE;
    add_definition(def_name, def_value);
    return TRUE;
}

/**
 * @brief Check if current position matches a string.
 *
 * @param buffer                The buffer
 * @param buffer_size           The buffer size
 * @param pos                   The current pos index
 * @param str                   The string to check
 *
 * @return TRUE or FALSE.
 */
static bool_t
matches_string_at_pos(const char *buffer, size_t buffer_size, size_t pos,
    const char *str)
{
    size_t len = strlen(str);
    if (pos + len > buffer_size)
        return FALSE;
    return strncmp(&buffer[pos], str, len) == 0;
}

/**
 * @brief Remove @def lines from buffer
 *
 * @param p             The parsing source struct
 */
static void
remove_def_lines(parsing_src_file_t *p)
{
    char *new_buffer = MALLOC(p->_buffer_size);
    size_t new_index = 0;
    size_t old_index = 0;

    while (old_index < p->_buffer_size) {
        if (matches_string_at_pos(p->_buffer, p->_buffer_size, old_index, "@def")) {
            while (old_index < p->_buffer_size && 
                   p->_buffer[old_index] != '\n' &&
                   p->_buffer[old_index] != '\r') {
                old_index++;
            }
            while (old_index < p->_buffer_size && 
                   (p->_buffer[old_index] == '\n' ||
                    p->_buffer[old_index] == '\r')) {
                old_index++;
            }
        } else {
            new_buffer[new_index++] = p->_buffer[old_index++];
        }
    }
    p->_buffer = new_buffer;
    p->_buffer_size = new_index;
}

/**
 * @brief Check if current position matches a string.
 *
 * @param p             The parsing source struct
 * @param str           The string to match
 *
 * @return TRUE or FALSE.
 */
static bool_t
matches_string(parsing_src_file_t *p, const char *str)
{
    return matches_string_at_pos(
        p->_buffer,
        p->_buffer_size,
        p->_current_index,
        str);
}

/**
 * @brief Prepass and get the array of words in the buffer
 *        and change them if needed by the definitions.
 *
 * @param p             The parsing source struct
 */
void
prepass_buffer(parsing_src_file_t *p)
{
    if (p == NULL)
        return;
    p->_current_index = 0;
    while (p->_current_index < p->_buffer_size) {
        if (!matches_string(p, "@def")) {
            p->_current_index++;
            continue;
        }
        if (!parse_def_directive(p)) {
            while (p->_current_index < p->_buffer_size && 
                   p->_buffer[p->_current_index] != '\n') {
                p->_current_index++;
            }
        }
    }
    remove_def_lines(p);
    replace_definitions(p);
}
