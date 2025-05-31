/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_cast
** File description:
** The AST for a cast
*/

#include "valka.h"

/**
 * @brief Make the AST for a cast declaration.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_cast(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;

    if (curr == NULL || curr->_next == NULL || curr->_next->_next == NULL)
        return NULL;
    node->_type = AST_CAST;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._cast._cast_type = get_data_type_from_token(curr->_next);
    move_token(current_token, 2);
    curr = *current_token;
    if (is_call_sym(curr)) {
        node->_ast_val._cast._val = make_ast_call_sym(current_token, parent);
        return node;
    }
    switch (curr->_type) {
        case TOKEN_SYMBOL:
            node->_ast_val._cast._val = make_ast_symbol(current_token, parent);
            break;
        case TOKEN_INT_LITERAL:
            node->_ast_val._cast._val = make_ast_int_literal(current_token, parent);
            break;
        default:
            PERROR("This cast is not handled yet.");
    }
    return node;
}
