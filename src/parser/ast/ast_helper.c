/*
** VALKA PROJECT, 2025
** src/parser/ast/ast_helper
** File description:
** Help by creating, removing, finding in ASTs
*/

#include "valka.h"

/**
 * @brief Get the parent recursively until we found the function parent.
 *
 * @param parent        The first parent.
 *
 * @return The function parent.
 */
ast_node_t *
get_func_parent(ast_program_t *prog)
{
    ast_node_t *node = NULL;

    if (prog == NULL)
        return NULL;
    node = prog->_parent;
    while (node != NULL && node->_type != AST_FUNCTION) {
        if (node->_parent)
            node = node->_parent->_parent; 
        else
            return NULL;
    }
    return node;
}
