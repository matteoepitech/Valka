/*
** VALKA PROJECT, 2025
** src/parser/tokens/token_helper
** File description:
** Token helper functions
*/

#include "valka.h"

/**
 * @brief Create a token by passing some parameters.
 *
 * @param type          The type of the token
 * @param start         The start of the content of the token in the buffer
 * @param length        The length of the token value
 * @param loc           The location of the token in the buffer (line, col)
 *
 * @return The token.
 */
token_t *
create_token(token_type_t type, const char *start, uint32_t length,
    location_t loc)
{
    token_t *token = MALLOC(sizeof(token_t));

    token->_type = type;
    token->_start = start;
    token->_loc = loc;
    token->_length = length;
    token->_next = NULL;
    return token;
}

/**
 * @brief Push a token and rewrite to the tail.
 *
 * @param tail           The tail of the tokens list
 * @param token          The token to push at the end
 *
 * @return The pushed list of tokens
 */
token_t *
push_token(token_t **tail, token_t *token)
{
    (*tail)->_next = token;
    *tail = (*tail)->_next;
    return *tail;
}

/**
 * @brief Is a start of an expression.
 *
 * @param token         The token
 *
 * @return TRUE or FALSE.
 */
bool_t
is_start_of_expression(token_t *token)
{
    token_t *after_call = NULL;

    if (token == NULL)
        return FALSE;
    if (token->_type == TOKEN_INT_LITERAL ||
        token->_type == TOKEN_FLOAT_LITERAL ||
        token->_type == TOKEN_SYMBOL ||
        token->_type == TOKEN_CAST)
        return TRUE;
    if (is_call_sym(token)) {
        after_call = token;
        while (after_call && after_call->_type != TOKEN_PARENT_CLOSE)
            after_call = after_call->_next;
        if (after_call && after_call->_next &&
            after_call->_next->_type == TOKEN_MATH_OPERATOR) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * @brief Is a call symbol.
 *
 * @param token         The token
 *
 * @return TRUE or FALSE.
 */
bool_t
is_call_sym(token_t *token)
{
    token_t *curr = NULL;
    int paren_count = 1;

    if (token == NULL|| token->_type != TOKEN_SYMBOL)
        return FALSE;
    if (token->_next == NULL|| token->_next->_type != TOKEN_PARENT_OPEN)
        return FALSE;
    curr = token->_next->_next;
    while (curr && paren_count > 0) {
        if (curr->_type == TOKEN_PARENT_OPEN)
            paren_count++;
        else if (curr->_type == TOKEN_PARENT_CLOSE)
            paren_count--;
        curr = curr->_next;
    }
    return (paren_count == 0);
}
