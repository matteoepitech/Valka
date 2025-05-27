/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_if
** File description:
** The AST for a if statement
*/

#include "valka.h"

/**
 * @brief Fill the content of the function.
 *
 * @param current_token  The current token position
 * @param node           The node of the function
 */
static void
fill_if_content(token_t **current_token, ast_node_t *node)
{
    ast_node_t *tmp_node = NULL;
    token_t *curr = *current_token;

    while (curr && curr->_type != TOKEN_BRACKET_CLOSE &&
        curr->_type != TOKEN_END) {
        tmp_node = dispatch_ast(current_token, node->_ast_val._if_statement._if_body);
        if (tmp_node == NULL) {
            move_token(current_token, 1);
            curr = *current_token;
            continue;
        }
        create_statement(node->_ast_val._if_statement._if_body, tmp_node);
        curr = *current_token;
    }
}

/**
 * @brief Make the AST for a if declaration.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_if(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;
     
    if (curr == NULL || curr->_next == NULL || curr->_next->_next == NULL)
        return NULL;
    node->_type = AST_IF;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._if_statement._if_body = MALLOC(sizeof(ast_program_t));
    node->_ast_val._if_statement._if_body->_statement_head = NULL;
    node->_ast_val._if_statement._if_body->_statement_tail = NULL;
    node->_ast_val._if_statement._if_body->_parent = node;
    node->_ast_val._if_statement._if_body->_statements_amount = 0;
    move_token(current_token, 2);
    node->_ast_val._if_statement._condition = dispatch_ast(current_token, parent);
    move_token(current_token, 1);
    if ((*current_token)->_type != TOKEN_BRACKET_OPEN)
        return NULL;
    move_token(current_token, 1);
    fill_if_content(current_token, node);
    if ((*current_token)->_type == TOKEN_BRACKET_CLOSE)
        move_token(current_token, 1);
    return node;
}
