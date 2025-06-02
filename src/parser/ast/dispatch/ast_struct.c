/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_struct.c
** File description:
** The AST for a struct
*/

#include "valka.h"

/**
 * @brief Fill the parameters.
 *
 * @param current_token The current token position
 * @param node          The AST node
 */
static void
fill_fields(token_t **current_token, ast_node_t *node)
{
    token_t *curr = *current_token;

    while (curr && curr->_type != TOKEN_BRACKET_CLOSE && curr->_type != TOKEN_END) {
        if (curr->_type != TOKEN_IDENTIFIER && curr->_type_id != IDENTIFIER_ID_VAR) {
            move_token(current_token, 1);
            curr = *current_token;
            continue;
        }
        move_token(current_token, 1);
        curr = *current_token;
        node->_ast_val._struct._fields_count++;
        node->_ast_val._struct._fields = REALLOC(node->_ast_val._struct._fields, sizeof(ast_node_t *) * node->_ast_val._struct._fields_count);
        node->_ast_val._struct._fields[node->_ast_val._struct._fields_count - 1] = MALLOC(sizeof(ast_node_t));
        node->_ast_val._struct._fields[node->_ast_val._struct._fields_count - 1]->_ast_val._var_decl._var_type = get_data_type_from_token(curr);
        node->_ast_val._struct._fields[node->_ast_val._struct._fields_count - 1]->_ast_val._var_decl._var_name = strndup_valka(curr->_next->_start,
            curr->_next->_length);
        move_token(current_token, 2);
        curr = *current_token;
    }
}

/**
 * @brief Make the AST for the function declaration
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_struct(token_t **current_token, UNUSED ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;

    if (curr == NULL)
        return NULL;
    node->_type = AST_STRUCT;
    node->_loc = curr->_loc;
    node->_parent = parent;
    move_token(current_token, 1);
    curr = *current_token;
    node->_ast_val._struct._struct_name = strndup_valka(curr->_start, curr->_length);
    node->_ast_val._struct._fields_count = 0;
    move_token(current_token, 1);
    curr = *current_token;
    if (curr->_type != TOKEN_BRACKET_OPEN)
        return NULL;
    fill_fields(current_token, node);
    print_type_token((*current_token)->_type);
    if ((*current_token)->_type == TOKEN_BRACKET_CLOSE)
        move_token(current_token, 1);
    return node;
}
