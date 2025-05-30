/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_index
** File description:
** The AST for an index
*/

#include "valka.h"

/**
 * @brief Make the AST for a index declaration.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_index(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;

    if (curr == NULL || curr->_next == NULL)
        return NULL;
    node->_type = AST_INDEX;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._index._sym = make_ast_symbol(current_token, parent);
    if ((*current_token)->_type == TOKEN_SQUARE_BRACKET_OPEN)
        move_token(current_token, 1);
    node->_ast_val._index._index_val = dispatch_ast(current_token, parent);
    if ((*current_token)->_type == TOKEN_SQUARE_BRACKET_CLOSE)
        move_token(current_token, 1);
    return node;
}
