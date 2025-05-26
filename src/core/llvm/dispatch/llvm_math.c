/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_math
** File description:
** LLVM for math declaration
*/

#include "valka.h"

/**
 * @brief LLVM math declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_math(ast_node_t *node, FILE *f, char *dest)
{
    bin_ope_t op = get_operator_with_char(node->_ast_val._binary_op._op);
    ast_node_t *left = node->_ast_val._binary_op._left;
    ast_node_t *right = node->_ast_val._binary_op._right;
    char *left_val = llvm_gen_value(left, f);
    char *right_val = llvm_gen_value(right, f);

    fprintf(f, "%%%s = %s i32 %%%s, %%%s\n", dest, op._llvm_ir,
        left_val, right_val);
    return OK_OUTPUT;
}
