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
    ast_node_t *tmp_val = node->_ast_val._return._value;
    char *tmp = NULL;

    if (tmp_val == NULL)
        return KO_OUTPUT;

    #if defined(ARCH_X86_64)
    if (strcmp(node->_parent->_parent->_ast_val._function._func_name, START_ENTRY_POINT) == 0)
        llvm_syscall(node, f, NULL, 60);
    #endif

    tmp = llvm_gen_value(tmp_val, f);
    if (tmp == NULL)
        return KO_OUTPUT;
    fprintf(f, "ret %s %%%s\n", ret_type, tmp);
    return OK_OUTPUT;
}
