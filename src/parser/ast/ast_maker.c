/*
** VALKA PROJECT, 2025
** src/parser/ast/ast_maker
** File description:
** Make the AST of a source code
*/

#include "valka.h"
#include "valka_parser.h"

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
dispatch_ast(token_t **current_token, ast_program_t *parent)
{
    uint32_t type_id = (*current_token)->_type_id;
    token_type_t type = (*current_token)->_type;

    if (type == TOKEN_SYMBOL && (*current_token)->_next->_type == TOKEN_ASSIGN)
        return make_ast_assign(current_token, parent);
    if (is_start_of_expression(*current_token) && get_next_token_after_call(*current_token)->_type == TOKEN_CONDITION)
        return make_ast_condition(current_token, parent);
    if (is_start_of_expression(*current_token))
        return make_ast_expression(current_token, parent);
    if (type == TOKEN_CAST)
        return make_ast_cast(current_token, parent);
    if (type == TOKEN_STRING)
        return make_ast_string(current_token, parent);
    if (type == TOKEN_IDENTIFIER) {
        switch (type_id) {
            case IDENTIFIER_ID_VAR:
                return make_ast_var(current_token, parent);
            case IDENTIFIER_ID_FUNC:
                return make_ast_func(current_token, parent);
            case IDENTIFIER_ID_RETURN:
                return make_ast_return(current_token, parent);
            case IDENTIFIER_ID_IF:
                return make_ast_if(current_token, parent);
            case IDENTIFIER_ID_FOR:
                return make_ast_for(current_token, parent);
            case IDENTIFIER_ID_WHILE:
                return make_ast_while(current_token, parent);
        }
    }
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
    prg->_parent = NULL;
    prg->_statements_amount = 0;
    current = p->_head_list;
    while (current && current->_type != TOKEN_END) {
        tmp_node = dispatch_ast(&current, NULL);
        if (tmp_node == NULL) {
            move_token(&current, 1);
            continue;
        }
        create_statement(prg, tmp_node);
    }
    return prg;
}
