/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_string
** File description:
** The AST for a string
*/

#include "valka.h"

/**
 * @brief Make the AST for a string declaration.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_string(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;

    if (curr == NULL)
        return NULL;
    node->_type = AST_STRING;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._string._value = strndup(curr->_start, curr->_length);
    move_token(current_token, 1);
    return node;
}
