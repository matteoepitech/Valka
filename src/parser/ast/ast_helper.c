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
    if (body->_parent == NULL || body->_parent->_parent == NULL)
        return get_param_decl_from_name(body, sym_name);
    return get_sym_decl_from_name(body->_parent->_parent, sym_name);
}

/**
 * @brief Add a symbol in the a ast_program_t to add all variables declarations.
 *
 * @param sym           The symbol   NODE
 * @param func          The function NODE
 *
 * @return Everything worked ?
 */
uint8_t
add_content_symbol(ast_node_t *sym, ast_program_t *prg)
{
    if (sym == NULL || prg == NULL)
        return KO_OUTPUT;
    prg->_content_symbols_count++;
    prg->_content_symbols = REALLOC(prg->_content_symbols, sizeof(ast_node_t *) * prg->_content_symbols_count);
    prg->_content_symbols[prg->_content_symbols_count - 1] = MALLOC(sizeof(ast_node_t));
    prg->_content_symbols[prg->_content_symbols_count - 1]->_ast_val = sym->_ast_val;
    return OK_OUTPUT;
}
