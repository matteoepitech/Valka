/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_condition
** File description:
** LLVM for condition declaration
*/

#include "valka.h"

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
    data_types_t data_type = get_highest_data_type(get_data_from_node(left), get_data_from_node(right));
    uint32_t op = node->_ast_val._condition._op_id;
    char *left_reg = llvm_gen_value(left, f, data_type);
    char *right_reg = llvm_gen_value(right, f, data_type);
    char *llvm_type = get_write_data_type(data_type);
    char *llvm_cmp = NULL;

    switch (op) {
        case OP_EQUAL:
            llvm_cmp = data_type._id == T_FLOAT ? "oeq" : "eq";
            break;
        case OP_NOT_EQUAL:
            llvm_cmp = data_type._id == T_FLOAT ? "one" : "ne";
            break;
        case OP_GREATER:
            llvm_cmp = data_type._id == T_FLOAT ? "ogt" : "sgt";
            break;
        case OP_LOWER:
            llvm_cmp = data_type._id == T_FLOAT ? "olt" : "slt";
            break;
        case OP_GREATER_EQ:
            llvm_cmp = data_type._id == T_FLOAT ? "oge" : "sge";
            break;
        case OP_LOWER_EQ:
            llvm_cmp = data_type._id == T_FLOAT ? "ole" : "sle";
            break;
        default:
            return 1;
    }
    fprintf(f, "%%%s = %ccmp %s %s %%%s, %%%s\n", dest,
        data_type._id == T_FLOAT ? 'f' : 'i', llvm_cmp, llvm_type, left_reg, right_reg);
    return OK_OUTPUT;
}
