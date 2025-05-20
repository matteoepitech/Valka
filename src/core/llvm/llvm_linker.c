/*
** VALKA PROJECT, 2025
** src/core/llvm/llvm_linker
** File description:
** The linker for LLVM source code into ASM
*/

#include "valka.h"

/**
 * @brief Compile the LLVM and link the whole thing using the
 *        rights parameters passed in the valkac arguments.
 */
void
compile_llvm_to_executable(void)
{
    int ret = system("llc out.ll -o out.s");

    if (ret != 0) {
        PERROR("Failed to compile the LLVM IR to assembly.");
        return;
    }
    ret = system("as out.s -o out.o");
    if (ret != 0) {
        PERROR("Failed to assemble the file.");
        return;
    }
    ret = system("ld -e __start -o a.out out.o");
    if (ret != 0) {
        PERROR("Failed to link the program.");
        return;
    }
    printf("\033[32;1m- Compilation and linking done! -\n\033[0m");
}
