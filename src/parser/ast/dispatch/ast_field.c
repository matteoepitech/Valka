/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_field
** File description:
** The AST for a field
*/

#include "valka.h"

/**
 * @brief Make an AST node for field.
 *
 * @param current_token          The current token
 * @param parent                 The parent
 * @param base_expr              The base expression (before this)
 *
 * @return The field AST node.
 */
ast_node_t *
make_ast_field(token_t **current_token, ast_program_t *parent, ast_node_t *base_expr)
{
    ast_node_t *field_node = NULL;
    token_t *curr = NULL;

    move_token(current_token, 1);
    curr = *current_token;
    if (curr == NULL || curr->_type != TOKEN_SYMBOL) {
        PERROR("Expected field name after '.'");
        return base_expr;
    }
    field_node = MALLOC(sizeof(ast_node_t));
    field_node->_type = AST_FIELD;
    field_node->_loc = curr->_loc;
    field_node->_parent = parent;
    field_node->_ast_val._field._field_name = strndup_valka(curr->_start, curr->_length);
    field_node->_ast_val._field._symbol = base_expr;
    move_token(current_token, 1);
    return field_node;
}
