/*
** VALKA PROJECT, 2025
** src/parser/function_prototype_helper
** File description:
** Handle functions prototypes
*/

#include "valka.h"

// @INFO this function use the extern variables defined in main.c
/**
 * @brief Add a function prototype.
 *
 * @param func_node     The AST node
 */
void
add_function_prototype(ast_node_t *func_node)
{
    functions_prototype_t *new_proto = NULL;
    uint32_t new_count = 0;

    if (func_node == NULL)
        return;
    new_count = functions_count + 1;
    functions_prototype = REALLOC(functions_prototype, sizeof(functions_prototype_t) * new_count);
    new_proto = &functions_prototype[functions_count];
    new_proto->_func_name = strdup_valka(func_node->_ast_val._function._func_name);
    new_proto->_return = func_node->_ast_val._function._return_data;
    new_proto->_params = func_node->_ast_val._function._params;
    new_proto->_params_count = func_node->_ast_val._function._params_count;
    functions_count = new_count;
}

/**
 * @brief Get a prototype from name.
 *
 * @param func_name     The function name
 *
 * @return The prototype.
 */
functions_prototype_t
get_prototype_from_name(const char *func_name)
{
    for (uint32_t i = 0; i < functions_count; i++) {
        if (strcmp(functions_prototype[i]._func_name, func_name) == 0)
            return functions_prototype[i];
    }
    return (functions_prototype_t) {0};
}
