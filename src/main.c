/*
** VALKA PROJECT, 2025
** src/main
** File description:
** Valka main file
*/

#include "valka.h"

/**
 * @brief Main function for valka binary.
 *
 * @param argc          ARGC
 * @param argv[]        ARGV
 *
 * @return Return status.
 */
int
main(UNUSED int argc, UNUSED char *argv[])
{
    parsing_src_file_t *p = NULL;
    ast_program_t *prg = NULL;
    FILE *out_llvm = NULL;

    if (argc <= 1)
        return cleanup_mem(KO_OUTPUT);
    p = tokenize_source_code(argv[1]);
    print_tokens(p);
    prg = make_ast(p);
    print_program(prg);
    out_llvm = create_llvm();
    generate_llvm_global(out_llvm, prg);
    close_llvm(out_llvm);
    return cleanup_mem(OK_OUTPUT);
}
