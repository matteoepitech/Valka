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
create_token(token_type_t type, const char *start, uint32_t length, location_t loc)
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
