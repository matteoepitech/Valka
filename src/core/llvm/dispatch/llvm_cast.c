/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_cast
** File description:
** LLVM for cast declaration
*/

#include "valka.h"

/**
 * @brief LLVM cast declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_cast(ast_node_t *node, FILE *f, char *dest)
{
    data_types_t from = get_data_from_node(node->_ast_val._cast._val);
    data_types_t to = node->_ast_val._cast._cast_type;
    const char *src = llvm_gen_value(node->_ast_val._cast._val, f, from);

    if (from._id == to._id) {
        fprintf(f, "%%%s = add %s 0, %%%s\n", dest, to._llvm_ir, src);
        return OK_OUTPUT;
    }
    if (from._id == T_I32 && to._id == T_BOOL) {
        fprintf(f, "%%%s = icmp ne i32 %%%s, 0\n", dest, src);
        return OK_OUTPUT;
    }
    if (from._id == T_I32 && to._id == T_CHAR) {
        fprintf(f, "%%%s = trunc i32 %%%s to i8\n", dest, src);
        return OK_OUTPUT;
    }
    if (from._id == T_I32 && to._id == T_FLOAT) {
        fprintf(f, "%%%s = sitofp i32 %%%s to double\n", dest, src);
        return OK_OUTPUT;
    }

    if (from._id == T_BOOL && to._id == T_I32) {
        fprintf(f, "%%%s = zext i1 %%%s to i32\n", dest, src);
        return OK_OUTPUT;
    }
    if (from._id == T_BOOL && to._id == T_CHAR) {
        fprintf(f, "%%%s = zext i1 %%%s to i8\n", dest, src);
        return OK_OUTPUT;
    }
    if (from._id == T_BOOL && to._id == T_FLOAT) {
        fprintf(f, "%%%s = uitofp i1 %%%s to double\n", dest, src);
        return OK_OUTPUT;
    }

    if (from._id == T_CHAR && to._id == T_I32) {
        fprintf(f, "%%%s = zext i8 %%%s to i32\n", dest, src);
        return OK_OUTPUT;
    }
    if (from._id == T_CHAR && to._id == T_BOOL) {
        fprintf(f, "%%%s = icmp ne i8 %%%s, 0\n", dest, src);
        return OK_OUTPUT;
    }
    if (from._id == T_CHAR && to._id == T_FLOAT) {
        fprintf(f, "%%%s = sitofp i8 %%%s to double\n", dest, src);
        return OK_OUTPUT;
    }

    if (from._id == T_FLOAT && to._id == T_I32) {
        fprintf(f, "%%%s = fptosi double %%%s to i32\n", dest, src);
        return OK_OUTPUT;
    }
    if (from._id == T_FLOAT && to._id == T_CHAR) {
        fprintf(f, "%%%s = fptosi double %%%s to i8\n", dest, src);
        return OK_OUTPUT;
    }
    if (from._id == T_FLOAT && to._id == T_BOOL) {
        fprintf(f, "%%%s = fcmp une double %%%s, 0.0\n", dest, src);
        return OK_OUTPUT;
    }
    PERROR("Cast not available");
    return KO_OUTPUT;
}
