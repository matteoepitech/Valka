/*
** VALKA PROJECT, 2025
** src/parser/tokens/token_after_call
** File description:
** Functions to get the next token after various call expressions
*/

#include "valka.h"

/**
 * @brief Skip all consecutive square bracket pairs [...].
 *
 * @param current_token Pointer to the current token (will be modified)
 *
 * @return The token after all brackets, or NULL if malformed.
 */
static token_t *
skip_square_brackets(token_t *current_token)
{
    token_t *curr = current_token;
    int bracket_count;
    
    while (curr && curr->_type == TOKEN_SQUARE_BRACKET_OPEN) {
        bracket_count = 1;
        curr = curr->_next;
        while (curr && bracket_count > 0) {
            if (curr->_type == TOKEN_SQUARE_BRACKET_OPEN)
                bracket_count++;
            else if (curr->_type == TOKEN_SQUARE_BRACKET_CLOSE)
                bracket_count--;
            curr = curr->_next;
        }
        if (bracket_count > 0) {
            return NULL;
        }
    }
    return curr;
}

/**
 * @brief Skip a field access (.field_name).
 *
 * @param current_token Pointer to the current token (should be TOKEN_DOT)
 *
 * @return The token after the field name, or current_token if not valid field.
 */
static token_t *
skip_field_access(token_t *current_token)
{
    token_t *curr = current_token;

    if (!curr || curr->_type != TOKEN_DOT)
        return curr;
    curr = curr->_next;
    if (curr && curr->_type == TOKEN_SYMBOL) {
        curr = curr->_next;
    }
    return curr;
}

/**
 * @brief Skip parentheses for function calls (...).
 *
 * @param current_token Pointer to the token after the opening parenthesis
 *
 * @return The token after the closing parenthesis, or NULL if malformed.
 */
static token_t *
skip_function_parentheses(token_t *current_token)
{
    token_t *curr = current_token;
    int paren_count = 1;

    while (curr && paren_count > 0) {
        if (curr->_type == TOKEN_PARENT_OPEN)
            paren_count++;
        else if (curr->_type == TOKEN_PARENT_CLOSE)
            paren_count--;
        curr = curr->_next;
    }
    if (paren_count > 0) {
        return NULL;
    }
    return curr;
}

/**
 * @brief Skip all chained postfix operations (brackets and field access).
 *
 * @param current_token The token to start from
 *
 * @return The token after all chained operations.
 */
static token_t *
skip_postfix_operations(token_t *current_token)
{
    token_t *curr = current_token;

    while (curr) {
        if (curr->_type == TOKEN_SQUARE_BRACKET_OPEN) {
            curr = skip_square_brackets(curr);
            if (!curr)
                return NULL;
        } else if (curr->_type == TOKEN_DOT) {
            curr = skip_field_access(curr);
        } else {
            break;
        }
    } 
    return curr;
}

/**
 * @brief Handle symbol with indexing (symbol[...]).
 *
 * @param node The symbol token
 *
 * @return The token after all indexing and field operations.
 */
static token_t *
handle_symbol_indexing(token_t *node)
{
    token_t *curr = node->_next;

    curr = skip_square_brackets(curr);
    if (!curr)
        return NULL;
    curr = skip_postfix_operations(curr);
    return curr;
}

/**
 * @brief Handle function calls with potential chained operations
 *
 * @param node The function name token
 *
 * @return The token after the complete function call and any chained operations
 */
static token_t *
handle_function_call(token_t *node)
{
    token_t *curr = node->_next->_next;
    
    curr = skip_function_parentheses(curr);
    if (!curr)
        return NULL;
    curr = skip_postfix_operations(curr);
    return curr;
}

/**
 * @brief Get the next real token after a call symbol.
 *
 * @param node The token to analyze
 *
 * @return The next token after the complete expression
 */
token_t *
get_next_token_after_call(token_t *node)
{
    if (!node)
        return NULL;
    if (node->_type == TOKEN_SYMBOL && node->_next && 
        node->_next->_type == TOKEN_SQUARE_BRACKET_OPEN) {
        return handle_symbol_indexing(node);
    }
    if (node->_type == TOKEN_SYMBOL && node->_next && 
        node->_next->_type == TOKEN_DOT) {
        return get_next_token_after_call(node->_next->_next);
    }
    if (node->_type == TOKEN_CAST) {
        return get_next_token_after_call(node->_next->_next);
    }
    if (node->_next && node->_next->_type == TOKEN_MATH_OPERATOR) {
        return get_next_token_after_call(node->_next->_next);
    }
    if (is_call_sym(node)) {
        return handle_function_call(node);
    }
    return node->_next;
}
