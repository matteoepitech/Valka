/*
** VALKA PROJECT, 2025
** src/parser/tokens/dispatch/token_condition
** File description:
** Token condition
*/

#include "valka.h"

/**
 * @brief This start is a valid condition ?
 *        STRNCMP used so some case not working.
 *
 * @param start         When the condition start
 *
 * @return TRUE or FALSE.
 */
bool_t
is_valid_condition(const char *start)
{
    int length = 0;

    for (int j = 0; condition_operators[j]._id != 0; j++) {
        length = strlen(condition_operators[j]._operator);
        if (strncmp(condition_operators[j]._operator, start, length) != 0)
            continue;
        if (!isspace(start[length]))
            continue;
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Condition token dispatch.
 *
 * @param p             The parsing src file structure
 *
 * @return The parsing src file structure.
 */
parsing_src_file_t *
condition_token(parsing_src_file_t *p)
{
    const char *start = &p->_buffer[p->_current_index];
    size_t i = p->_current_index + 1;
    size_t length = 0;
    token_t *token = NULL;

    for (int j = 0; condition_operators[j]._id != 0; j++) {
        length = strlen(condition_operators[j]._operator);
        if (strncmp(condition_operators[j]._operator, start, length) == 0) {
            token = create_token(TOKEN_CONDITION, start, length, p->_current_loc);
            token->_type_id = condition_operators[j]._id;
            i += length;
            break;
        }
    }
    push_token(&p->_tail_list, token);
    p->_current_index = i;
    return p;
}
