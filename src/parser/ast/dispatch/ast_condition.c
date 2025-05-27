/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_condition
** File description:
** The AST for a condition
*/

#include "valka.h"

/**
 * @brief Make the AST for a condition declaration.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_condition(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;

    if (curr == NULL || curr->_next == NULL || curr->_next->_next == NULL)
        return NULL;
    node->_type = AST_CONDITION;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._condition._node_a = make_ast_expression(current_token, parent);
    node->_ast_val._condition._op_id = (*current_token)->_type_id;
    move_token(current_token, 1);
    node->_ast_val._condition._node_b = make_ast_expression(current_token, parent);
    return node;
}
