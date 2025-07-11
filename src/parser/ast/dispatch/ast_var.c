/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_var
** File description:
** The AST for a var
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
make_ast_var(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;

    if (curr == NULL || curr->_next == NULL ||
        curr->_next->_next == NULL ||
        curr->_next->_next->_next == NULL ||
        curr->_next->_next->_next->_next == NULL || node == NULL)
        return NULL;
    node->_type = AST_VAR_DECL;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._var_decl._var_name = strndup_valka(curr->_next->_next->_start,
        curr->_next->_next->_length);
    node->_ast_val._var_decl._var_type = get_data_type_from_token(curr->_next);
    node->_ast_val._var_decl._value = NULL;
    move_token(current_token, 3);
    if ((*current_token)->_type != TOKEN_ASSIGN) {
        return node;
    }
    move_token(current_token, 1);
    node->_ast_val._var_decl._value = dispatch_ast(current_token, parent);
    return node;
}
