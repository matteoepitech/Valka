/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_call_sym
** File description:
** LLVM for call symbol declaration
*/

#include "valka.h"

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
        arg_vars[i] = llvm_gen_value(node->_ast_val._call_sym._args[i], f, prototype._params[i]->_ast_val._var_decl._var_type);
    }
    if (dest == NULL)
        fprintf(f, "call %s @%s(", prototype._return._llvm_ir, func_name);
    else
        fprintf(f, "%%%s = call %s @%s(", dest, prototype._return._llvm_ir, func_name);
    for (uint32_t i = 0; i < argc; i++) {
        fprintf(f, "%s %%%s", prototype._params[i]->_ast_val._var_decl._var_type._llvm_ir, arg_vars[i]);
        if (i < argc - 1)
            fprintf(f, ", ");
    }
    fprintf(f, ")\n\n");
    return OK_OUTPUT;
}
