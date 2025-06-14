/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_call_sym
** File description:
** The AST for a call sym
*/

#include "valka.h"

/**
 * @brief Fill the parameters for a call symbol.
 *
 * @param current_token The current token
 * @param parent        The parent
 * @param node          The AST node
 */
static void
fill_call_sym_parameters(token_t **current_token, ast_program_t *parent,
    ast_node_t *node)
{
    ast_node_t **args = NULL;
    uint32_t args_c = 0;

    while (*current_token && (*current_token)->_type != TOKEN_PARENT_CLOSE) {
        args = REALLOC(args, sizeof(ast_node_t *) * (args_c + 1));
        args[args_c] = dispatch_ast(current_token, parent);
        args_c++;
        if (*current_token && (*current_token)->_type == TOKEN_COMMA) {
            move_token(current_token, 1);
        }
    }
    node->_ast_val._call_sym._args = args;
    node->_ast_val._call_sym._args_count = args_c;
    if ((*current_token)->_type == TOKEN_PARENT_CLOSE)
        move_token(current_token, 1);
}

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
   
    node->_type = AST_CALL_SYM;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._call_sym._args_count = 0;
    node->_ast_val._call_sym._args = NULL;
    node->_ast_val._call_sym._sym_name = strndup_valka(curr->_start, curr->_length);
    move_token(current_token, 1);
    curr = *current_token;
    if (curr == NULL || curr->_type != TOKEN_PARENT_OPEN)
        return node;
    move_token(current_token, 1);
    curr = *current_token;
    if ((*current_token)->_type == TOKEN_PARENT_CLOSE) {
        move_token(current_token, 1);
        return node;
    }
    fill_call_sym_parameters(current_token, parent, node);
    return node;
}
