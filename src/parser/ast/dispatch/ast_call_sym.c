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
    int parent_count = 1;
    
    node->_type = AST_CALL_SYM;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._call_sym._sym_name = strndup(curr->_start, curr->_length);
    move_token(current_token, 1);
    curr = *current_token;
    if (curr == NULL || curr->_type != TOKEN_PARENT_OPEN)
        return node;
    move_token(current_token, 1); 
    while (*current_token && parent_count > 0) {
        if ((*current_token)->_type == TOKEN_PARENT_OPEN)
            parent_count++;
        else if ((*current_token)->_type == TOKEN_PARENT_CLOSE)
            parent_count--;
        move_token(current_token, 1);
    }
    return node;
}
