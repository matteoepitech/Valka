/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_string
** File description:
** LLVM for string declaration
*/

#include "valka.h"

/**
 * @brief LLVM string declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_string(ast_node_t *node, FILE *f, char *dest)
{
    uint32_t size_string = 0;
    char *name_sym = node->_ast_val._string._name_sym;

    if (node == NULL || f == NULL || dest == NULL)
        return KO_OUTPUT;
    size_string = strlen(node->_ast_val._string._value) + 1;
    fprintf(f, "%%%s = getelementptr inbounds [%d x i8], [%d x i8]* @%s, i32 0, i32 0\n", dest, size_string, size_string, name_sym);
    return OK_OUTPUT;
}
