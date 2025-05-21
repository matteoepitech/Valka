/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_digit.c
** File description:
** The AST for a digit (INT, UINT, FLOAT, ...)
*/

#include "valka.h"

/**
 * @brief Make the AST for the number declarations.
 *        This can handle 32 bits, 64 bits, ...
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_int_literal(token_t **current_token, UNUSED ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;
    char *tmp_val_string = NULL;
    char *endptr = NULL;
    long long val_l = 0;

    if (curr == NULL)
        return NULL;
    tmp_val_string = strndup(curr->_start, curr->_length);
    node->_type = AST_LITERAL_INT;
    node->_loc = curr->_loc;
    val_l = strtoll(tmp_val_string, &endptr, 10);
    if (endptr == tmp_val_string || *endptr != '\0') {
        move_token(current_token, 1);
        return NULL;
    }
    node->_ast_val._int_literal._value = val_l;
    move_token(current_token, 1);
    return node;
}
