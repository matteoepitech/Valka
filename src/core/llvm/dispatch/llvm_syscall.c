/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_syscall
** File description:
** LLVM syscall declaration
*/

#include "valka.h"

/** 
 * macOS ARM64 syscall : /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/sys/syscall.h
 * linux x86_64 syscall : /usr/include/x86_64-linux-gnu/sys/syscall.h
 */

/**
 * @brief LLVM syscall declaration.
 *
 * @param node           The AST node
 * @param f              The FILE to write in
 *
 * @return Everything worked?
 */
uint8_t
llvm_syscall(UNUSED ast_node_t *node, FILE *f, char *dest, uint32_t force_sys)
{
    uint32_t syscall_id = force_sys;

    if (dest == NULL)
        fprintf(f, "call void asm sideeffect ");
    else
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
    fprintf(f, "\"r,r,r,r,r,r,r,~{rax},~{rdi},~{rsi},~{rdx},~{r10},~{r8},~{r9},~{rcx},~{r11},~{memory}\" ");
    fprintf(f, "(i64 %d, i64 0, i64 0, i64 0, i64 0, i64 0, i64 0)\n", syscall_id); 
    fprintf(f, "\n");

    #elif defined(ARCH_ARM64)
    fprintf(f, "\"");
    fprintf(f, "mov x8, $0; "); 
    fprintf(f, "mov x0, $1; ");
    fprintf(f, "mov x1, $2; ");
    fprintf(f, "mov x2, $3; ");
    fprintf(f, "mov x3, $4; ");
    fprintf(f, "mov x4, $5; ");
    fprintf(f, "mov x5, $6; ");
    fprintf(f, "svc #0");
    fprintf(f, "\", ");
    fprintf(f, "\"r,r,r,r,r,r,r,~{x8},~{x0},~{x1},~{x2},~{x3},~{x4},~{x5},~{memory}\" ");
    fprintf(f, "(i64 %d, i64 0, i64 0, i64 0, i64 0, i64 0, i64 0)\n", syscall_id);

    if (syscall_id == SYS_exit)
        fprintf(f, "ret %s %d\n", node->_parent->_parent->_ast_val._function._return_data._llvm_ir, 0);

    fprintf(f, "\n");

    #endif
    return OK_OUTPUT;
}
