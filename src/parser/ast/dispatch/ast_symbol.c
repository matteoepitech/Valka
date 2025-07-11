/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_symbol
** File description:
** The AST for a symbol
*/

#include "valka.h"

/**
* @brief Parse postfix operations like [0] or .field
*
* @param current_token          The current token
* @param parent                 The parent AST
* @param base_node              The node
*
* @return The node.
*/
static ast_node_t *
parse_postfix_operations(token_t **current_token, ast_program_t *parent, ast_node_t *base_node)
{
    ast_node_t *current_node = base_node;
    token_t *curr = *current_token;

    while (curr != NULL) {
        if (curr->_type == TOKEN_SQUARE_BRACKET_OPEN) {
            current_node = make_ast_index(current_token, parent, current_node);
        } else if (curr->_type == TOKEN_DOT) {
            current_node = make_ast_field(current_token, parent, current_node);
        } else {
            break;
        }
        curr = *current_token;
    } 
    return current_node;
}

/**
* @brief Create a symbol node.
*
* @param current_token          The current token
* @param parent                 The parent AST
*
* @return The node.
*/
static ast_node_t *
create_symbol_node(token_t **current_token, ast_program_t *parent)
{
    token_t *curr = *current_token;
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    
    node->_type = AST_SYMBOL;
    node->_loc = curr->_loc;
    node->_parent = parent;
    node->_ast_val._symbol._sym_name = strndup_valka(curr->_start, curr->_length); 
    move_token(current_token, 1);
    return node;
}
/**
 * @brief Make the AST for a symbol.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_symbol(token_t **current_token, ast_program_t *parent)
{
    token_t *curr = *current_token;
    ast_node_t *node = NULL;
    
    if (curr == NULL || curr->_type != TOKEN_SYMBOL)
        return NULL;
    if (curr->_next && curr->_next->_type == TOKEN_PARENT_OPEN)
        return make_ast_call_sym(current_token, parent);
    node = create_symbol_node(current_token, parent);
    return parse_postfix_operations(current_token, parent, node);
}
