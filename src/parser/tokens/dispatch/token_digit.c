/*
** VALKA PROJECT, 2025
** src/parser/tokens/dispatch/token_digit
** File description:
** Token digit
*/

#include "valka.h"

/**
 * @brief Digit token dispatch.
 *
 * @param p             The parsing src file structure
 *
 * @return The parsing src file structure.
 */
parsing_src_file_t *
digit_token(parsing_src_file_t *p)
{
    const char *start = &p->_buffer[p->_current_index];
    size_t i = p->_current_index;
    size_t length = 0;
    token_t *token = NULL;

    while (i < p->_buffer_size && (isdigit(p->_buffer[i]))) {
        i++;
    }
    length = i - p->_current_index;
    token = create_token(TOKEN_INT_LITERAL, start, length, p->_current_loc);
    push_token(&p->_tail_list, token);
    p->_current_index = i;
    return p;
}
