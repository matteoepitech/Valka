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
char *
llvm_math(ast_node_t *node, FILE *f)
{
    char *tmp_name = get_random_var_name();
    bin_ope_t op = get_operator_with_char(node->_ast_val._binary_op._op);
    ast_node_t *left = node->_ast_val._binary_op._left;
    ast_node_t *right = node->_ast_val._binary_op._right;

    if (left->_type == AST_LITERAL_INT && right->_type == AST_LITERAL_INT)
        fprintf(f, "%%%s = %s %s %d, %d\n", tmp_name, op._llvm_ir, "i32",
            left->_ast_val._int_literal._value,
            right->_ast_val._int_literal._value);
    return tmp_name;
}
