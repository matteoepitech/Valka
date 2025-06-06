/*
** VALKA PROJECT, 2025
** src/main
** File description:
** Valka main file
*/

#include "valka.h"

// Used to generate random tmp variable
uint32_t register_id = 0;

// Used for prototypes functions/structures
functions_prototype_t *functions_prototype = NULL;
uint32_t functions_count = 0;
structs_prototype_t *structures_prototype = NULL;
uint32_t structures_count = 0;

// Used for definitions of variables
definition_t *definitions_src = NULL;
uint32_t definitions_count = 0;

// All Valka data types (extern in valka_parser.h)
const data_types_t data_types[] = {
    {T_I32, "i32", "i32", sizeof(int) * 8, 0, {0}, 0},
    {T_BOOL, "bool", "i1", 1, 0, {0}, 0},
    {T_CHAR, "char", "i8", sizeof(char) * 8, 0, {0}, 0},
    {T_VOID, "void", "void", 0, 0, {0}, 0},
    {T_VARG, "...", "...", 0, 0, {0}, 0},
    {T_FLOAT, "float", "double", sizeof(float) * 8, 0, {0}, 0},
    {T_STRUCT, "", "", 0, 0, {0}, 0},
    {T_I64, "long", "i64", sizeof(int) * 2 * 8, 0, {0}, 0},
    {0, "", "", 0, 0, {0}, 0},
};

// All Valka binary operation (extern in valka_parser.h)
const bin_ope_t bin_operations[] = {
    {'+', "add"},
    {'-', "sub"},
    {'/', "sdiv"},
    {'*', "mul"},
    {'%', "srem"},
    {0, ""}
};

// All Valka conditions operation (extern in valka_parser.h)
const condition_operator_t condition_operators[] =  {
    {"==", OP_EQUAL},
    {">=", OP_GREATER_EQ},
    {"<=", OP_LOWER_EQ},
    {">", OP_GREATER},
    {"<", OP_LOWER},
    {"!=", OP_NOT_EQUAL},
    {"", 0}
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
    UNUSED ast_program_t *prg = NULL;
    UNUSED FILE *out_llvm = NULL;

    if (argc <= 1)
        return cleanup_mem(KO_OUTPUT);
    p = tokenize_source_code(argv[1]);
    print_tokens(p);
    prg = make_ast(p);
    print_program(prg);
    out_llvm = create_llvm();
    collect_all_strings(prg, out_llvm);
    generate_llvm_global(out_llvm, prg);
    close_llvm(out_llvm);
    compile_llvm_to_executable();
    return cleanup_mem(OK_OUTPUT);
}
