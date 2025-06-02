/*
** VALKA PROJECT, 2025
** src/parser/ast/dispatch/ast_index
** File description:
** The AST for an index
*/

#include "valka.h"

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
        } else {
            PERROR("Expected ']' after index expression");
            break;
        }
    }
    return count;
}

/**
 * @brief Make an AST node for index.
 *
 * @param current_token          The current token
 * @param parent                 The parent
 * @param base_expr              The base expression (before this)
 *
 * @return The index AST node.
 */
ast_node_t *
make_ast_index(token_t **current_token, ast_program_t *parent, ast_node_t *base_expr)
{
    ast_node_t *index_node = MALLOC(sizeof(ast_node_t));
    ast_node_t *indices[MAX_INDICES_DEPTH];
    uint32_t count = 0;

    index_node->_type = AST_INDEX;
    index_node->_loc = (*current_token)->_loc;
    index_node->_parent = parent;
    index_node->_ast_val._index._sym = base_expr;
    count = store_indices(current_token, parent, indices);
    index_node->_ast_val._index._indices = MALLOC(sizeof(ast_node_t*) * count);
    for (uint32_t i = 0; i < count; i++) {
        index_node->_ast_val._index._indices[i] = indices[i];
    }
    index_node->_ast_val._index._index_count = count;
    return index_node;
}
