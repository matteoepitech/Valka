/*
** VALKA PROJECT, 2025
** src/parser/ast/ast_statement
** File description:
** Help by creating, removing, finding statement
*/

#include "valka.h"

/**
 * @brief Create a statement and increment the prg statements amount.
 *
 * @param prg           The program source code AST
 * @param ast           The ast
 *
 * @return The statement added in the linked list.
 */
ast_statement_t *
create_statement(ast_program_t *prg, ast_node_t *ast)
{
    ast_statement_t *state = MALLOC(sizeof(ast_statement_t));

    if (prg == NULL || ast == NULL)
        return NULL;
    state->_ast_id = prg->_statements_amount;
    state->_ast_node = ast;
    state->_next = NULL;
    if (prg->_statement_head == NULL) {
        prg->_statement_head = state;
        prg->_statement_tail = state;
    } else {
        prg->_statement_tail->_next = state;
        prg->_statement_tail = state;
    }
    prg->_statements_amount++;
    return state;
}
