/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_index
** File description:
** The AST for an index
*/
#include "valka.h"

/**
 * @brief Get the symbol. It's the same function as the make_ast_symbol but
 *        for index. So there will be some changes in the future here.
 *
 * @param current_token         The current token
 * @param parent                The parent
 *
 * @return The node.
 */
static ast_node_t *
get_symbol_index(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    node->_type = AST_SYMBOL;
    node->_loc = (*current_token)->_loc;
    node->_parent = parent;
    node->_ast_val._symbol._sym_name = strndup_valka(
        (*current_token)->_start, (*current_token)->_length);
    move_token(current_token, 1);
    return node;
}

/**
 * @brief Store all index in the indices array and return the count total.
 *
 * @param current_token                 The current token
 * @param parent                        The parent
 * @param indices[MAX_INDICES_DEPTH]    The array of index
 *
 * @return The count of index.
 */
static uint32_t
store_indices(token_t **current_token, ast_program_t *parent, ast_node_t *indices[MAX_INDICES_DEPTH])
{
    uint32_t count = 0;
    while ((*current_token) && (*current_token)->_type == TOKEN_SQUARE_BRACKET_OPEN && count < MAX_INDICES_DEPTH) {
        move_token(current_token, 1);
        indices[count] = dispatch_ast(current_token, parent);
        if ((*current_token) && (*current_token)->_type == TOKEN_SQUARE_BRACKET_CLOSE) {
            move_token(current_token, 1);
            count++;
        }
    }
    return count;
}

/**
 * @brief Make the AST for a index declaration.
 *
 * @param current_token The current token
 *
 * @return The AST node.
 */
ast_node_t *
make_ast_index(token_t **current_token, ast_program_t *parent)
{
    ast_node_t *node = MALLOC(sizeof(ast_node_t));
    token_t *curr = *current_token;
    ast_node_t *indices[MAX_INDICES_DEPTH];
    uint32_t count = 0;
    
    if (curr == NULL || curr->_next == NULL)
        return NULL;
    node->_type = AST_INDEX;
    node->_loc = curr->_loc;
    node->_parent = parent;
    if ((*current_token)->_type == TOKEN_PARENT_OPEN) {
        PERROR("Not handling index on result of function!");
    } 
    node->_ast_val._index._sym = get_symbol_index(current_token, parent);    
    count = store_indices(current_token, parent, indices);
    node->_ast_val._index._indices = MALLOC(sizeof(ast_node_t*) * count);
    for (uint32_t i = 0; i < count; i++) {
        node->_ast_val._index._indices[i] = indices[i];
    }
    node->_ast_val._index._index_count = count;
    return node;
}
