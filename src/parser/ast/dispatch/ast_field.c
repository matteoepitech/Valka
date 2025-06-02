/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_field
** File description:
** The AST for a field
*/

#include "valka.h"

/**
 * @brief Make the AST for a field.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_field(token_t **current_token, ast_program_t *parent)
{
    token_t *curr = *current_token;
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    ast_node_t *field_node = NULL;

    node->_type = AST_SYMBOL;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._symbol._sym_name = strndup_valka(curr->_start, curr->_length);
    move_token(current_token, 1);
    curr = *current_token;
    while (curr && curr->_type == TOKEN_DOT) {
        move_token(current_token, 1);
        curr = *current_token;
        field_node = MALLOC(sizeof(ast_node_t));
        field_node->_type = AST_FIELD;
        field_node->_loc = curr->_loc;
        field_node->_parent = parent;
        field_node->_ast_val._field._field_name = strndup_valka(curr->_start, curr->_length);
        field_node->_ast_val._field._symbol = node;
        node = field_node;
        move_token(current_token, 1);
        curr = *current_token;
    }
    return node;
}
