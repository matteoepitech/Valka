/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_assign
** File description:
** The AST for a assignment
*/

#include "valka.h"

/**
 * @brief Make the AST for an assignment of variable.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_assign(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;

    node->_type = AST_ASSIGNMENT;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._assignment._assigned = make_ast_symbol(current_token, parent);
    if ((*current_token)->_type == TOKEN_ASSIGN)
        move_token(current_token, 1);
    node->_ast_val._assignment._value = dispatch_ast(current_token, parent);
    return node;
}
