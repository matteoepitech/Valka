/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_call_sym
** File description:
** LLVM for call symbol declaration
*/

#include "valka.h"

/**
 * @brief Write the prototype to make a cast.
 *
 * @param prototype     The prototype
 * @param f             The FILE to write in
 */
static void
write_cast_prototype(functions_prototype_t prototype, FILE *f)
{
    bool_t need_to_cast = FALSE;

    for (uint32_t i = 0; i < prototype._params_count; i++) {
        if (prototype._params[i]->_ast_val._var_decl._var_type._id == T_VARG)
            need_to_cast = TRUE;
    }
    if (need_to_cast == FALSE)
        return;
    fprintf(f, "(");
    for (uint32_t i = 0; i < prototype._params_count; i++) {
        if (i != 0)
            fprintf(f, ", ");
        fprintf(f, "%s", prototype._params[i]->_ast_val._var_decl._var_type._llvm_ir);
    }
    fprintf(f, ") ");
}

/**
 * @brief LLVM call symbol declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_call_sym(ast_node_t *node, FILE *f, char *dest)
{
    const char *func_name = node->_ast_val._call_sym._sym_name;
    functions_prototype_t prototype = get_prototype_from_name(func_name);
    uint32_t argc = node->_ast_val._call_sym._args_count;
    char **arg_vars = MALLOC(sizeof(char *) * argc);

    for (uint32_t i = 0; i < argc; i++) {
        arg_vars[i] = llvm_gen_value(node->_ast_val._call_sym._args[i], f, get_data_from_node(node->_ast_val._call_sym._args[i]));
    }
    if (dest != NULL)
        fprintf(f, "%%%s = ", dest);
    fprintf(f, "call %s ", prototype._return._llvm_ir);
    write_cast_prototype(prototype, f);
    fprintf(f, "@%s(", func_name);
    for (uint32_t i = 0; i < argc; i++) {
        fprintf(f, "%s %%%s", get_data_from_node(node->_ast_val._call_sym._args[i])._llvm_ir, arg_vars[i]);
        if (i < argc - 1)
            fprintf(f, ", ");
    }
    fprintf(f, ")\n\n");
    return OK_OUTPUT;
}
