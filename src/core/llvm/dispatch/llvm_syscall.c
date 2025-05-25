/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_syscall
** File description:
** LLVM syscall declaration
*/

#include "valka.h"
#include "valka_parser.h"

/** 
 * macOS ARM64 syscall : /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/syscall.h
 * linux x86_64 syscall : /usr/include/x86_64-linux-gnu/sys/syscall.h
 */

/**
 * @brief Generate the tmp parameters casted to 64.
 *
 * @param node           The AST node
 * @param args_count     The number of arguments
 * @param args_reg[6]    The arguments final tmp symbol names
 * @param f              The FILE to write in
 */
static void
generate_tmp_casted_parameters(ast_node_t *node, uint32_t args_count,
    char *args_reg[6], FILE *f)
{
    char *arg_32 = NULL;
    char *arg_64 = NULL;
    
    for (uint32_t i = 0; i < args_count && i < 6; i++) {
        arg_32 = llvm_gen_value(node->_ast_val._call_sym._args[i], f);
        arg_64 = get_random_var_name();
        fprintf(f, "%%%s = sext i32 %%%s to i64\n", arg_64, arg_32);
        fprintf(f, "%%%s = sext i32 %%%s to i64\n", arg_64, arg_32);
        args_reg[i] = arg_64;
    }
}

/**
 * @brief A exit need to be followed by a return.
 *
 * @param node          The AST node
 * @param f             The FILE to write in
 */
UNUSED static void exit_specification(ast_node_t *node, FILE *f)
{
    char *tmp_ret = llvm_gen_value(node->_ast_val._call_sym._args[1], f);

    fprintf(f, "ret %s %%%s\n\n",
        node->_parent->_parent->_ast_val._function._return_data._llvm_ir,
        tmp_ret);
}

/**
 * @brief LLVM syscall declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_syscall(ast_node_t *node, FILE *f, char *dest)
{
    char *args_reg[6] = {NULL};
    uint32_t args_count = node->_ast_val._call_sym._args_count;

    if (dest == NULL)
        dest = get_random_var_name();
    generate_tmp_casted_parameters(node, args_count, args_reg, f);
    fprintf(f, "%%%s = call i64 asm ", dest);

    #if defined(ARCH_X86_64)
    fprintf(f, "\"");
    fprintf(f, "mov $0, %%rax; ");
    fprintf(f, "mov $1, %%rdi; ");
    fprintf(f, "mov $2, %%rsi; ");
    fprintf(f, "mov $3, %%rdx; ");
    fprintf(f, "mov $4, %%r10; ");
    fprintf(f, "mov $5, %%r8; ");
    fprintf(f, "mov $6, %%r9; ");
    fprintf(f, "syscall");
    fprintf(f, "\", ");
    fprintf(f, "\"r");
    for (int i = 1; i < 7; i++)
        fprintf(f, ",r");
    fprintf(f, ",~{rax},~{rdi},~{rsi},~{rdx},~{r10},~{r8},~{r9},~{rcx},~{r11},~{memory}\" ");
    fprintf(f, "(i64 %%%s", args_reg[0] ? args_reg[0] : "0");
    for (uint32_t i = 1; i < args_count && i < 7; i++)
        fprintf(f, ", i64 %%%s", args_reg[i]);
    for (uint32_t i = args_count; i < 7; i++)
        fprintf(f, ", i64 0");
    fprintf(f, ")\n\n");

    #elif defined(ARCH_ARM64)
    fprintf(f, "\"");
    fprintf(f, "mov x16, $0; ");
    fprintf(f, "mov x0, $1; ");
    fprintf(f, "mov x1, $2; ");
    fprintf(f, "mov x2, $3; ");
    fprintf(f, "mov x3, $4; ");
    fprintf(f, "mov x4, $5; ");
    fprintf(f, "mov x5, $6; ");
    fprintf(f, "svc #0x80");
    fprintf(f, "\", ");
    fprintf(f, "\"r");
    for (int i = 1; i < 7; i++)
        fprintf(f, ",r");
    fprintf(f, ",~{x16},~{x0},~{x1},~{x2},~{x3},~{x4},~{x5},~{memory}\" ");
    fprintf(f, "(i64 %%%s", args_reg[0] ? args_reg[0] : "0");
    for (uint32_t i = 1; i < args_count && i < 7; i++)
        fprintf(f, ", i64 %%%s", args_reg[i]);
    for (uint32_t i = args_count; i < 7; i++)
        fprintf(f, ", i64 0");
    fprintf(f, ")\n\n");
    #endif
    
    if (node->_ast_val._call_sym._args[0]->_ast_val._int_literal._value == SYS_exit)
        exit_specification(node, f);

    return OK_OUTPUT;
}
