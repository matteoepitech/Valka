/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_var
** File description:
** LLVM for variable declaration
*/

#include "valka.h"

/**
 * @brief LLVM var declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_var(ast_node_t *node, FILE *f)
{
    const char *var_name = node->_ast_val._var_decl._var_name;
    ast_node_t *value_node = node->_ast_val._var_decl._value;
    data_types_t data = node->_ast_val._var_decl._var_type;
    UNUSED char *tmp_var = NULL;

    fprintf(f, "%%%s = alloca %s\n", var_name, data._llvm_ir);
    if (value_node->_type == AST_BINARY_OP) {
        tmp_var = llvm_math(value_node, f);
        fprintf(f, "store %s %%%s, %s* %%%s\n\n", data._llvm_ir, tmp_var,
            data._llvm_ir, var_name);
        return OK_OUTPUT;
    }
    if (value_node->_type == AST_CALL_SYM) {
        tmp_var = get_random_var_name();
        llvm_call_sym(value_node, f, tmp_var);
        fprintf(f, "store %s %%%s, %s* %%%s\n\n", data._llvm_ir, tmp_var,
            data._llvm_ir, var_name);
        return OK_OUTPUT;
    }
    fprintf(f, "store %s %d, %s* %%%s\n\n", data._llvm_ir,
        value_node->_ast_val._int_literal._value, data._llvm_ir, var_name);
    return OK_OUTPUT;
}
