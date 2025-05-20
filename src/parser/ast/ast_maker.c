/*
** VALKA PROJECT, 2025
** src/parser/ast/ast_maker
** File description:
** Make the AST of a source code
*/

#include "valka.h"
#include "valka_parser.h"
#include <stdio.h>

/**
 * @brief Move the token.
 *
 * @param current_token The current token
 * @param move_token    The move amount
 */
void
move_token(token_t **current_token, int move_token)
{
    for (int i = 0; i < move_token; i++) {
        if (current_token != NULL)
            *current_token = (*current_token)->_next;
        else
            break;
    }
}

/**
 * @brief Dispatch and use the right AST function.
 *
 * @param current_token The current token
 *
 * @return The ast node.
 */
ast_node_t *
dispatch_ast(token_t **current_token)
{
    token_type_t type = (*current_token)->_type;

    if (type == TOKEN_IDENTIFIER)
        return make_ast_var(current_token);
    if (type == TOKEN_INT_LITERAL)
        return make_ast_int_literal(current_token);
    return NULL;
}

/**
 * @brief Make the AST of 1 source code.
 *
 * @param p             The source code tokenized
 *
 * @return The ast final program.
 */
ast_program_t *
make_ast(parsing_src_file_t *p)
{
    ast_node_t *tmp_node = NULL;
    ast_program_t *prg = NULL;
    token_t *current = NULL;

    if (p == NULL)
        return NULL;
    prg = MALLOC(sizeof(ast_program_t));
    prg->_statement_head = NULL;
    prg->_statement_tail = NULL;
    prg->_statements_amount = 0;
    current = p->_head_list;
    while (current && current->_type != TOKEN_END) {
        tmp_node = dispatch_ast(&current);
        if (tmp_node == NULL) {
            move_token(&current, 1);
            continue;
        }
        create_statement(prg, tmp_node);
    }
    return prg;
}
