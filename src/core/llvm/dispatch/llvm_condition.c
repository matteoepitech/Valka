/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_condition
** File description:
** LLVM for condition declaration
*/

#include "valka.h"
#include "valka_parser.h"

/**
 * @brief LLVM condition declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_condition(ast_node_t *node, FILE *f, char *dest)
{
    ast_node_t *left = node->_ast_val._condition._node_a;
    ast_node_t *right = node->_ast_val._condition._node_b;
    uint32_t op = node->_ast_val._condition._op_id;
    char *llvm_cmp = NULL;
    char *left_reg = llvm_gen_value(left, f, get_data_with_id(T_I32));
    char *right_reg = llvm_gen_value(right, f, get_data_with_id(T_I32));

    switch (op) {
        case OP_EQUAL:
            llvm_cmp = "eq";
            break;
        case OP_NOT_EQUAL:
            llvm_cmp = "ne";
            break;
        case OP_GREATER:
            llvm_cmp = "sgt";
            break;
        case OP_LOWER:
            llvm_cmp = "slt";
            break;
        case OP_GREATER_EQ:
            llvm_cmp = "sge";
            break;
        case OP_LOWER_EQ:
            llvm_cmp = "sle";
            break;
        default:
            return 1;
    }
    fprintf(f, "%%%s = icmp %s i32 %%%s, %%%s\n", dest, llvm_cmp, left_reg, right_reg);
    return OK_OUTPUT;
}
