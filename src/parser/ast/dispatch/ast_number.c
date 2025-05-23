/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_digit.c
** File description:
** The AST for a digit (INT, UINT, FLOAT, ...)
*/

#include "valka.h"

/**
 * @brief Get the priority of an operator.
 *
 * @param op    The character that represent the operator
 *
 * @return The priority.
 */
static int
get_priority(char op)
{
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

/**
 * @brief Make the parsing of the expression using the priority.
 *
 * @param current_token          The current token
 * @param parent                 The parent ast
 * @param min_prio               The minimum priority
 *
 * @return The final AST.
 */
static ast_node_t *
parse_expression(token_t **current_token, ast_program_t *parent, int min_prio)
{
    ast_node_t *left = NULL;
    ast_node_t *right = NULL;
    ast_node_t *binary_node = NULL;
    token_t *curr = NULL;
    char op;
    int precedence;

    left = make_ast_int_literal(current_token, parent);
    if (left == NULL)
        return NULL;
    while (1) {
        curr = *current_token;
        if (curr == NULL || curr->_type != TOKEN_MATH_OPERATOR)
            break;
        op = curr->_start[0];
        precedence = get_priority(op);
        if (precedence < min_prio)
            break;
        move_token(current_token, 1);
        right = parse_expression(current_token, parent, precedence + 1);
        if (right == NULL)
            return NULL;
        binary_node = MALLOC(sizeof(ast_node_t));
        binary_node->_type = AST_BINARY_OP;
        binary_node->_loc = left->_loc;
        binary_node->_parent = parent;
        binary_node->_ast_val._binary_op._left = left;
        binary_node->_ast_val._binary_op._op = op;
        binary_node->_ast_val._binary_op._right = right;
        left = binary_node;
    }
    return left;
}

/**
 * @brief Make the AST for the number declarations.
 *        This can handle 32 bits, 64 bits, ...
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_int_literal(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = NULL;
    token_t *curr = *current_token;
    char *tmp_val_string = NULL;
    char *endptr = NULL;
    long long val_l = 0;

    if (curr == NULL || curr->_type != TOKEN_INT_LITERAL)
        return NULL;
    tmp_val_string = strndup(curr->_start, curr->_length);
    val_l = strtoll(tmp_val_string, &endptr, 10);
    if (endptr == tmp_val_string || *endptr != '\0')
        return NULL;
    node = MALLOC(sizeof(ast_node_t));
    node->_type = AST_LITERAL_INT;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._int_literal._value = val_l;
    move_token(current_token, 1);
    return node;
}


/**
 * @brief Make the AST for the math expression declaration.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_expression(token_t **current_token, ast_program_t *parent)
{
    return parse_expression(current_token, parent, 0);
}
