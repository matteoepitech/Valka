/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_symbol
** File description:
** The AST for a symbol
*/

#include "valka.h"

/**
 * @brief Make the AST for a symbol.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_symbol(token_t **current_token, ast_program_t *parent)
{
    token_t *curr = *current_token;
    ast_node_t *node = MALLOC(sizeof(ast_node_t));

    if (curr == NULL || curr->_type != TOKEN_SYMBOL)
        return NULL;
    if (curr->_next && curr->_next->_type == TOKEN_PARENT_OPEN)
        return make_ast_call_sym(current_token, parent);
    if (curr->_next && curr->_next->_type == TOKEN_SQUARE_BRACKET_OPEN)
        return make_ast_index(current_token, parent);
    if (curr->_next && curr->_next->_type == TOKEN_DOT)
        return make_ast_field(current_token, parent);
    node->_type = AST_SYMBOL;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._symbol._sym_name = strndup_valka(curr->_start, curr->_length);
    move_token(current_token, 1);
    return node;
}
