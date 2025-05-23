/*
** VALKA PROJECT, 2025
** src/parser/tokens/dispatch/token_bin_operation
** File description:
** Token binary operation
*/

#include "valka.h"

/**
 * @brief Binary operation token dispatch.
 *
 * @param p             The parsing src file structure
 *
 * @return The parsing src file structure.
 */
parsing_src_file_t *
bin_operation_token(parsing_src_file_t *p)
{
    const char *start = &p->_buffer[p->_current_index];
    size_t i = p->_current_index + 1;
    size_t length = 1;
    token_t *token = NULL;

    token = create_token(TOKEN_MATH_OPERATOR, start, length, p->_current_loc);
    push_token(&p->_tail_list, token);
    p->_current_index = i;
    return p;
}
