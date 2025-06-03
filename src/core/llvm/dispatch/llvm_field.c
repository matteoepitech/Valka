/*
** VALKA PROJECT, 2025
** src/core/llvm/dispatch/llvm_field
** File description:
** LLVM for field declaration
*/

#include "valka.h"
#include "valka_parser.h"

/**
 * @brief LLVM generate field from structure.
 *
 * @param node          The AST node
 * @param f             The FILE to write in
 * @param dest          The destination of the field
 * @param load_val      Do we need to load the val or just get var ptr
 *
 * @return Everything worked?
 */
uint8_t
llvm_field(ast_node_t *node, FILE *f, char *dest, bool_t load_val)
{
    ast_node_t *parent = node->_ast_val._field._symbol;
    data_types_t parent_type = get_data_from_node(parent);
    char *parent_sym = NULL;
    char *ptr_tmp = get_random_var_name();
    char *llvm_struct_type = get_write_data_type(parent_type, FALSE);
    const char *field_name = node->_ast_val._field._field_name;
    structs_prototype_t structure = get_struct_prototype_from_name(llvm_struct_type);
    uint32_t field_index = get_struct_field_index(structure, field_name);
    char *field_type = get_write_data_type(structure._fields[field_index]->_ast_val._var_decl._var_type, FALSE);
    
    if (parent->_type == AST_FIELD) {
        parent_sym = get_random_var_name();
        llvm_field(parent, f, parent_sym, FALSE);
    } else if (parent->_type == AST_SYMBOL) {
        parent_sym = parent->_ast_val._symbol._sym_name;
    } else {
        parent_sym = llvm_gen_value(parent, f, parent_type, FALSE);
    }
    if (load_val == FALSE) {
        fprintf(f,
            "%%%s = getelementptr inbounds %s, %s* %%%s, i32 0, i32 %u\n",
            dest, llvm_struct_type, llvm_struct_type, parent_sym, field_index);
    } else {
        fprintf(f,
            "%%%s = getelementptr inbounds %s, %s* %%%s, i32 0, i32 %u\n",
            ptr_tmp, llvm_struct_type, llvm_struct_type, parent_sym, field_index);
        fprintf(f, "%%%s = load %s, %s* %%%s\n", dest, field_type, field_type, ptr_tmp);
    }
    return OK_OUTPUT;
}
