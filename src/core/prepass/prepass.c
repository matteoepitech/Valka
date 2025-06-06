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
 * @param p The parsing structure
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
 * @param p The parsing structure
 *
 * @return The extracted word (must be freed) or NULL.
 */
static char *
extract_word(parsing_src_file_t *p)
{
    size_t start = p->_current_index;
    char *word = NULL;
    size_t len = 0;

    while (p->_current_index < p->_buffer_size && 
           !isalnum(p->_buffer[p->_current_index]) && 
           p->_buffer[p->_current_index] != '_') {
        p->_current_index++;
    } 
    start = p->_current_index;
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
 * @param p The parsing structure
 *
 * @return The extracted value or NULL.
 */
static char *
extract_value(parsing_src_file_t *p)
{
    size_t start = p->_current_index;
    char *value = NULL;
    size_t len = 0;

    skip_whitespace(p);
    start = p->_current_index;
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
 * @param p The parsing structure
 *
 * @return TRUE if successfully parsed, FALSE otherwise.
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
 * @param p   The parsing structure
 * @param str The string to match
 *
 * @return TRUE if matches, FALSE otherwise.
 */
static bool_t
matches_string(parsing_src_file_t *p, const char *str)
{
    size_t len = strlen(str);

    if (p->_current_index + len > p->_buffer_size)
        return FALSE;    
    return strncmp(&p->_buffer[p->_current_index], str, len) == 0;
}

/**
 * @brief Replace definitions in the buffer.
 *
 * @param p The parsing structure
 */
static void
replace_definitions(parsing_src_file_t *p)
{
    size_t new_buffer_size = p->_buffer_size * 2;
    char *new_buffer = MALLOC(new_buffer_size);
    size_t new_index = 0;
    size_t old_index = 0;

    while (old_index < p->_buffer_size) {
        bool_t found_replacement = FALSE;
        for (uint32_t i = 0; i < definitions_count && !found_replacement; i++) {
            if (definitions_src[i]._def == NULL)
                continue;
            size_t def_len = strlen(definitions_src[i]._def);
            
            if (old_index + def_len <= p->_buffer_size &&
                strncmp(&p->_buffer[old_index], definitions_src[i]._def, def_len) == 0) {
                bool_t is_complete_word = TRUE;
                
                if (old_index > 0 && 
                    (isalnum(p->_buffer[old_index - 1]) || 
                     p->_buffer[old_index - 1] == '_'))
                    is_complete_word = FALSE;
                
                if (old_index + def_len < p->_buffer_size &&
                    (isalnum(p->_buffer[old_index + def_len]) || 
                     p->_buffer[old_index + def_len] == '_'))
                    is_complete_word = FALSE;
                
                if (is_complete_word && definitions_src[i]._val) {
                    size_t val_len = strlen(definitions_src[i]._val);
 
                    while (new_index + val_len >= new_buffer_size) {
                        new_buffer_size *= 2;
                        new_buffer = REALLOC(new_buffer, new_buffer_size);
                    }
 
                    strcpy(&new_buffer[new_index], definitions_src[i]._val);
                    new_index += val_len;
                    old_index += def_len;
                    found_replacement = TRUE;
                }
            }
        } 
        if (found_replacement == FALSE) {
            if (new_index >= new_buffer_size) {
                new_buffer_size *= 2;
                new_buffer = REALLOC(new_buffer, new_buffer_size);
            }
            new_buffer[new_index++] = p->_buffer[old_index++];
        }
    }
    p->_buffer = new_buffer;
    p->_buffer_size = new_index;
    p->_current_index = 0;
}

/**
 * @brief Remove @def lines from buffer
 *
 * @param p The parsing structure
 */
static void
remove_def_lines(parsing_src_file_t *p)
{
    char *new_buffer = MALLOC(p->_buffer_size);
    size_t new_index = 0;
    size_t old_index = 0;

    while (old_index < p->_buffer_size) {
        if (matches_string((parsing_src_file_t*) &(parsing_src_file_t)
            {
            ._buffer = p->_buffer,
            ._buffer_size = p->_buffer_size,
            ._current_index = old_index
            },
            "@def")) {
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
 * @brief Prepass and get the array of words in the buffer
 *        and change them if needed by the definitions.
 *
 * @param p     Parsing source structure
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
    p->_current_index = 0;
}
