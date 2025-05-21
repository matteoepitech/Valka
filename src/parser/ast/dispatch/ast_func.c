/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_func.c
** File description:
** The AST for a a function
*/

#include "valka.h"

/**
 * @brief Is the main function of the program ? (entrypoint)
 *
 * @param node          The AST node
 *
 * @return The final AST node.
 */
static ast_node_t *
is_main_function(ast_node_t *node)
{
    if (strcmp(node->_ast_val._function._func_name, "main") == 0) {
        node->_ast_val._function._func_name = strdup("_start");
    }
    return node;
}

/**
 * @brief Make the AST for the function declaration
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_func(token_t **current_token, UNUSED ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;
    ast_node_t *tmp_node = NULL;

    if (curr == NULL)
        return NULL;
    node->_type = AST_FUNCTION;
    node->_loc = curr->_loc;
    node->_ast_val._function._func_name = strndup(curr->_next->_start, curr->_next->_length);
    node->_ast_val._function._func_content = MALLOC(sizeof(ast_program_t));
    node->_ast_val._function._func_content->_statement_head = NULL;
    node->_ast_val._function._func_content->_statement_tail = NULL;
    node->_ast_val._function._func_content->_statements_amount = 0;
    move_token(current_token, 2);
    curr = *current_token;
    if (curr->_type != TOKEN_BRACKET_OPEN)
        return NULL;
    move_token(current_token, 1);
    while (curr && curr->_type != TOKEN_BRACKET_CLOSE && curr->_type != TOKEN_END) {
        tmp_node = dispatch_ast(current_token, node->_ast_val._function._func_content);
        if (tmp_node == NULL) {
            move_token(current_token, 1);
            curr = *current_token;
            continue;
        }
        create_statement(node->_ast_val._function._func_content, tmp_node);
        curr = *current_token;
    }
    return is_main_function(node);
}
