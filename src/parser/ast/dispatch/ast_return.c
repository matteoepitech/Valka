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
    if (curr->_next->_type == TOKEN_SYMBOL) {
        node->_ast_val._return._return_id = RETURN_ID_SYMBOL;
        node->_ast_val._return._sym_name = strndup(curr->_next->_start,
            curr->_next->_length);
        move_token(current_token, 2);
    }
    if (curr->_next->_type == TOKEN_INT_LITERAL) {
        node->_ast_val._return._return_id = RETURN_ID_INT;
        move_token(current_token, 1);
        node->_ast_val._return._value = dispatch_ast(current_token, parent);
    }
    node->_ast_val._return._return_data = parent->_parent->_ast_val._function._return_data;
    return node;
}
