/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_increment
** File description:
** The AST for a increment (i++, i--)
*/

#include "valka.h"

/**
 * @brief Create the node of 1, for the i++ or i--.
 *
 * @param parent                 The parent
 *
 * @return The AST node.
 */
static ast_node_t *
create_one_increment_node(ast_node_t *parent)
{
    ast_node_t *node = NULL;

    if (parent == NULL)
        return NULL;
    node = MALLOC(sizeof(ast_node_t));
    node->_loc = parent->_loc;
    node->_parent = parent->_parent;
    node->_type = AST_LITERAL_INT;
    node->_ast_val._int_literal._value = 1;
    return node;
}

/**
 * @brief Create the node of the symbol + 1 or - 1.
 *
 * @param parent                 The parent
 *
 * @return The AST node.
 */
static ast_node_t *
create_operation_node(ast_node_t *parent, char op)
{
    ast_node_t *node = NULL;
    ast_node_t *one_node = NULL;

    if (parent == NULL)
        return NULL;
    one_node = create_one_increment_node(parent);
    if (one_node == NULL)
        return NULL;
    node = MALLOC(sizeof(ast_node_t));
    node->_loc = parent->_loc;
    node->_parent = parent->_parent;
    node->_type = AST_BINARY_OP;
    node->_ast_val._binary_op._op = op;
    node->_ast_val._binary_op._left = parent->_ast_val._assignment._assigned;
    node->_ast_val._binary_op._right = one_node;
    return node;
}

/**
 * @brief Make an AST node for increment.
 *
 * @param current_token          The current token
 * @param parent                 The parent
 * @param base_expr              The base expression (before this)
 *
 * @return The increment AST node.
 */
ast_node_t *
make_ast_increment(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *inc_node = NULL;
    token_t *curr = *current_token;

    if (curr->_next == NULL || curr->_next->_type != TOKEN_MATH_OPERATOR ||
        (curr->_next->_start[0] != '+' && curr->_next->_start[0] != '-'))
        return NULL;
    if (curr->_next->_next == NULL ||
        curr->_next->_next->_type != TOKEN_MATH_OPERATOR ||
        (curr->_next->_next->_start[0] != '+' &&
        curr->_next->_next->_start[0] != '-'))
        return NULL;
    inc_node = MALLOC(sizeof(ast_node_t));
    inc_node->_type = AST_ASSIGNMENT;
    inc_node->_loc = curr->_loc;
    inc_node->_parent = parent;
    inc_node->_ast_val._assignment._assigned = make_ast_symbol(current_token, parent);
    move_token(current_token, 1);
    curr = *current_token;
    inc_node->_ast_val._assignment._value = create_operation_node(inc_node, curr->_start[0]);
    move_token(current_token, 1);
    return inc_node;
}
