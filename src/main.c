/*
** VALKA PROJECT, 2025
** src/main
** File description:
** Valka main file
*/

#include "valka.h"

// Used to generate random tmp variable
uint32_t register_id = 0;

// All Valka data types (extern in valka_parser.h)
const data_types_t data_types[] = {
    {T_I32, "i32", "i32"},
    {T_BOOL, "bool", "i1"},
    {T_CHAR, "char", "i8"},
    {0, "", ""},
};

// All Valka binary operation (extern in valka_parser.h)
const bin_ope_t bin_operations[] = {
    {'+', "add"},
    {'-', "sub"},
    {'/', "sdiv"},
    {'*', "mul"},
    {0, ""}
};

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
    compile_llvm_to_executable();
    return cleanup_mem(OK_OUTPUT);
}
