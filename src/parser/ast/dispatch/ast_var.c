/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_var
** File description:
** The AST for a var
*/

#include "valka.h"

/**
 * @brief Set the token type of the data if the data is existing.
 *
 * @param token         The token
 */
static data_types_t
set_data_type(token_t *token)
{
    for (int i = 0; data_types[i]._id != 0; i++) {
        if (strncmp(&token->_start[1], data_types[i]._valka_ir,
            token->_length - 2) == 0 && 
            token->_length - 2 == strlen(data_types[i]._valka_ir)) {
            return data_types[i];
        }
    }
    return (data_types_t) {0};
}


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
    node->_ast_val._var_decl._var_name = strndup(curr->_next->_next->_start,
        curr->_next->_next->_length);
    node->_ast_val._var_decl._var_type = set_data_type(curr->_next);
    move_token(current_token, 4);
    node->_ast_val._var_decl._value = dispatch_ast(current_token, parent);
    return node;
}
