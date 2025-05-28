/*
** VALKA PROJECT, 2025
** src/core/llvm/llvm_manager
** File description:
** LLVM Manager
*/

#include "valka.h"

/**
 * @brief Dispatch the LLVM generating to get the right function.
 *
 * @param f             The FILE
 * @param cur           The current statement
 *
 * @return Everything worked?
 */
static uint8_t dispatch_llvm(FILE *f, ast_statement_t *cur)
{
    ast_node_t *node = cur->_ast_node;

    if (node->_type == AST_ASSIGNMENT)
        return llvm_assign(node, f);
    if (node->_type == AST_IF)
        return llvm_if(node, f);
    if (node->_type == AST_CALL_SYM)
        return llvm_call_sym(node, f, NULL);
    if (node->_type == AST_VAR_DECL)
        return llvm_var(node, f);
    if (node->_type == AST_FUNCTION)
        return llvm_func(node, f);
    if (node->_type == AST_RETURN)
        return llvm_return(node, f);
    return KO_OUTPUT;
}

/**
 * @brief Create the LLVM file.
 *
 * @return The LLVM file opened.
 */
FILE *
create_llvm(void)
{
    FILE *llvm_out = fopen("out.ll", "w");

    if (llvm_out == NULL) {
        PERROR("Cannot create out.ll");
        return NULL;
    }
    return llvm_out;
}

/**
 * @brief Close the LLVM.
 *
 * @param f              The FILE
 *
 * @return Status of the operation.
 */
uint8_t
close_llvm(FILE *f)
{
    if (f == NULL)
        return KO_OUTPUT;
    fclose(f);
    return OK_OUTPUT;
}

/**
 * @brief Generate the LLVM.
 *
 * @param f             The FILE
 * @param prg           The program
 */
void
generate_llvm_global(FILE *f, ast_program_t *prg)
{
    ast_statement_t *cur = prg->_statement_head;

    while (cur) {
        if (dispatch_llvm(f, cur) == KO_OUTPUT)
            break;
        cur = cur->_next;
    }
}
