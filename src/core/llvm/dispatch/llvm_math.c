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
    data_types_t data_type = get_highest_data_type(get_data_from_node(left), get_data_from_node(right));
    char *left_val = llvm_gen_value(left, f, data_type);
    char *right_val = llvm_gen_value(right, f, data_type);
    char *llvm_type = get_write_data_type(data_type);
    const char *op_ir = op._llvm_ir;

    if (data_type._id == T_FLOAT) {
        if (op._operator == '/' || op._operator == '%')
            op_ir++;
        fprintf(f, "%%%s = f%s %s %%%s, %%%s\n", dest, op_ir, llvm_type, left_val, right_val);
    } else
        fprintf(f, "%%%s = %s %s %%%s, %%%s\n", dest, op._llvm_ir, llvm_type, left_val, right_val);
    return OK_OUTPUT;
}
