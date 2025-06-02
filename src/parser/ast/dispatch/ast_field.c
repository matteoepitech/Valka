/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_field
** File description:
** The AST for a field
*/

#include "valka.h"
#include "valka_parser.h"

/**
 * @brief Get the symbol. It's the same function as the make_ast_symbol but
 *        for field. So there will be some changes in the future here.
 *
 * @param current_token         The current token
 * @param parent                The parent
 *
 * @return The node.
 */
static ast_node_t *
get_symbol_field(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));

    node->_type = AST_SYMBOL;
    node->_loc = (*current_token)->_loc;
    node->_parent = parent;
    node->_ast_val._symbol._sym_name = strndup_valka(
        (*current_token)->_start, (*current_token)->_length);
    move_token(current_token, 1);
    return node;
}

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

    node->_type = AST_FIELD;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._field._symbol = get_symbol_field(current_token, parent);
    move_token(current_token, 1);
    curr = *current_token;
    node->_ast_val._field._field_name = strndup_valka(curr->_start, curr->_length);
    move_token(current_token, 1);
    return node;
}
