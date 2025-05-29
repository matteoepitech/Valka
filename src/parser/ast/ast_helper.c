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

/**
 * @brief Get a param from name. Only for parameters of function body.
 *
 * @param body          The body content, if body, else body, func, content,..
 * @param sym_name      The symbol name to find
 *
 * @return The AST node.
 */
ast_node_t *
get_param_decl_from_name(ast_program_t *body, char *sym_name)
{
    ast_node_t *func_body = get_func_parent(body);

    if (func_body == NULL)
        return NULL;
    for (uint32_t i = 0; i < func_body->_ast_val._function._params_count; i++) {
        if (strcmp(sym_name, func_body->_ast_val._function._params[i]->_ast_val._var_decl._var_name) == 0)
            return func_body->_ast_val._function._params[i];
    }
    return NULL;
}

/**
 * @brief Get a symbol from name. Used to get the type of the symbol for eg.
 *
 * @param body          The body content, if body, else body, func, content,..
 * @param sym_name      The symbol name to find
 *
 * @return The AST node.
 */
ast_node_t *
get_sym_decl_from_name(ast_program_t *body, char *sym_name)
{
    if (body == NULL || sym_name == NULL)
        return NULL;
    for (uint32_t i = 0; i < body->_content_symbols_count; i++) {
        if (strcmp(sym_name, body->_content_symbols[i]->_ast_val._var_decl._var_name) == 0)
            return body->_content_symbols[i];
    }
    return get_param_decl_from_name(body, sym_name);
}

/**
 * @brief Get the right type using only the AST node.
 *
 * @param node          The AST node
 *
 * @return The data type.
 */
data_types_t
get_data_from_node(ast_node_t *node)
{
    if (node->_type == AST_CALL_SYM)
        return get_prototype_from_name(node->_ast_val._call_sym._sym_name)._return;
    if (node->_type == AST_LITERAL_INT)
        return get_data_with_id(T_I32);
    if (node->_type == AST_SYMBOL)
        return get_sym_decl_from_name(node->_parent, node->_ast_val._call_sym._sym_name)->_ast_val._var_decl._var_type;
    if (node->_type == AST_STRING)
        return get_data_with_id(T_CHAR_P);
    if (node->_type == AST_BINARY_OP)
        return get_data_from_node(node->_ast_val._binary_op._left);
    PERROR("This type is not handled yet!");
    return (data_types_t) {0};
}
