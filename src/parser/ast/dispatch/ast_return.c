/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_return
** File description:
** The AST for a return
*/

#include "valka.h"

/**
 * @brief Make the AST for the variable declaration.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_return(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;

    if (curr == NULL || curr->_next == NULL || curr->_next->_next == NULL)
        return NULL;
    node->_type = AST_RETURN;
    node->_loc = curr->_loc;
    node->_ast_val._return._sym_name = NULL;
    node->_parent = parent;
    node->_ast_val._return._return_data = get_func_parent(parent)->_ast_val._function._return_data;
    node->_ast_val._return._return_id = 0;
    move_token(current_token, 1);
    node->_ast_val._return._value = dispatch_ast(current_token, parent);
    return node;
}
