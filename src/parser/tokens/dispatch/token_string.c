/*
** VALKA PROJECT, 2025
** src/parser/tokens/dispatch/token_string
** File description:
** Token string
*/

#include "valka.h"

/**
 * @brief String token dispatch.
 *
 * @param p             The parsing src file structure
 *
 * @return The parsing src file structure.
 */
parsing_src_file_t *
string_token(parsing_src_file_t *p)
{
    const char *start = &p->_buffer[p->_current_index + 1];
    size_t i = p->_current_index + 1;
    size_t length = 0;
    token_t *token = NULL;

    while (p->_buffer[i] != '\"' && i < p->_buffer_size) {
        i++;
    }
    length = i - p->_current_index - 1;
    token = create_token(TOKEN_STRING, start, length, p->_current_loc);
    push_token(&p->_tail_list, token);
    p->_current_index = i + 1;
    return p;
}
