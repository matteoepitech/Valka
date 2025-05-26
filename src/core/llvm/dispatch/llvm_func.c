/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_func
** File description:
** LLVM for function declaration
*/

#include "valka.h"

/**
 * @brief LLVM declaration func declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_declare_func(ast_node_t *node, FILE *f)
{
    const char *func_name = node->_ast_val._function._func_name;
    data_types_t func_ret = node->_ast_val._function._return_data;

    fprintf(f, "declare %s @%s(", func_ret._llvm_ir, func_name);
    for (uint32_t i = 0; i < node->_ast_val._function._params_count; i++) {
        if (i != 0)
            fprintf(f, ", ");
        fprintf(f, "%s %%%s",
            node->_ast_val._function._params[i]->_ast_val._var_decl._var_type._llvm_ir,
            node->_ast_val._function._params[i]->_ast_val._var_decl._var_name);
    }
    fprintf(f, ")\n\n");
    return OK_OUTPUT;
}

/**
 * @brief LLVM func declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_func(ast_node_t *node, FILE *f)
{
    const char *func_name = node->_ast_val._function._func_name;
    data_types_t func_ret = node->_ast_val._function._return_data;
    ast_program_t *func_content = node->_ast_val._function._func_content;

    if (func_content->_statements_amount == -1)
        return llvm_declare_func(node, f);
    fprintf(f, "define %s @%s(", func_ret._llvm_ir, func_name);
    for (uint32_t i = 0; i < node->_ast_val._function._params_count; i++) {
        if (i != 0)
            fprintf(f, ", ");
        fprintf(f, "%s %%%s",
            node->_ast_val._function._params[i]->_ast_val._var_decl._var_type._llvm_ir,
            node->_ast_val._function._params[i]->_ast_val._var_decl._var_name);
    }
    fprintf(f, ")\n");
    fprintf(f, "{\n");
    fprintf(f, "entry:\n\n");
    generate_llvm_global(f, func_content);
    if (node->_ast_val._function._return_data._id == T_VOID)
        fprintf(f, "ret void\n");
    fprintf(f, "}\n\n");
    return OK_OUTPUT;
}
