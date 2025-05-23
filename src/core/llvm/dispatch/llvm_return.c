/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_return
** File description:
** LLVM for return declaration
*/

#include "valka.h"

/**
 * @brief LLVM return declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_return
** File description:
** LLVM for return declaration
*/

#include "valka.h"

/**
 * @brief LLVM return declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_return(ast_node_t *node, FILE *f)
{
    const char *ret_type = node->_ast_val._return._return_data._llvm_ir;
    const char *ret_var_tmp = "__ret_val__";
    ast_node_t *tmp_val = node->_ast_val._return._value;

    if (tmp_val == NULL)
        return KO_OUTPUT;
    if (tmp_val->_type == AST_SYMBOL) {
        fprintf(f, "%%%s = load %s, %s* %%%s\n",
            ret_var_tmp, ret_type, ret_type, tmp_val->_ast_val._symbol._sym_name);
        fprintf(f, "ret %s %%%s\n", ret_type, ret_var_tmp);
        return OK_OUTPUT;
    }
    if (tmp_val->_type == AST_CALL_SYM) {
        llvm_call_sym(tmp_val, f, ret_var_tmp);
        fprintf(f, "ret %s %%%s\n", ret_type, ret_var_tmp);
        return OK_OUTPUT;
    }
    if (tmp_val->_type == AST_LITERAL_INT) {
        fprintf(f, "ret %s %d\n", ret_type,
            tmp_val->_ast_val._int_literal._value);
        return OK_OUTPUT;
    }
    if (tmp_val->_type == AST_BINARY_OP)
        fprintf(f, "ret %s %%%s\n", ret_type, llvm_math(tmp_val, f));
    return OK_OUTPUT;
}
