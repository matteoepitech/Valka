/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_call_sym
** File description:
** The AST for a call sym
*/

#include "valka.h"

/**
 * @brief Make the AST for a call symbol.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_call_sym(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;
    uint32_t count_parent = 0;

    node->_type = AST_CALL_SYM;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._call_sym._sym_name = strndup(curr->_start, curr->_length);
    if (curr->_next && curr->_next->_type == TOKEN_PARENT_OPEN) {
        while (curr->_type != TOKEN_PARENT_CLOSE) {
            count_parent++;
            curr = curr->_next;
        }
    }
    move_token(current_token, count_parent);
    return node;
}
