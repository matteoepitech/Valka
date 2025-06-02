/*
** VALKA PROJECT, 2025
** src/core/llvm/llvm_helper
** File description:
** LLVM helper
*/

#include "valka.h"

/**
 * @brief Generate the parameter loading from a function.
 *
 * @param node          The AST node
 * @param f             The FILE to write in
 * @param tmp           The destination
 *
 * @return If we found the symbol or not.
 */
static uint8_t
generate_symbol_from_param(ast_node_t *node, FILE *f, char **tmp)
{
    ast_node_t *func_node = get_func_parent(node->_parent);
    uint32_t func_params_count = func_node->_ast_val._function._params_count;
    ast_node_t **func_params = func_node->_ast_val._function._params;

    for (uint32_t i = 0; i < func_params_count; i++) {
        if (strcmp(func_params[i]->_ast_val._var_decl._var_name, node->_ast_val._symbol._sym_name) == 0) {
            if (func_params[i]->_ast_val._var_decl._var_type._ptr_level > 0) {
                *tmp = strdup(node->_ast_val._symbol._sym_name);
                return OK_OUTPUT;
            }
            generate_load_literal(*tmp,
                func_params[i]->_ast_val._var_decl._var_type,
                func_params[i]->_ast_val._var_decl._var_name, f);
            return OK_OUTPUT;
        }
    }
    return KO_OUTPUT;
}

/**
 * @brief Generate a load of a literal (float / int).
 *
 * @param dest          The destination
 * @param var_type      The var type
 * @param var_name      The var name
 * @param f             The FILE to write in
 *
 * @return The OK_OUTPUT or KO_OUTPUT.
 */
uint8_t
generate_load_literal(char *dest, data_types_t var_type, char *var_name, FILE *f)
{
    if (var_type._id == 0 || dest == NULL || var_name == NULL || f == NULL)
        return KO_OUTPUT;
    if (var_type._id == T_FLOAT) {
        fprintf(f, "%%%s = fadd %s %.6e, %%%s\n",
            dest, get_write_data_type(var_type), 0.0f, var_name);
    }
    else {
        fprintf(f, "%%%s = add %s 0, %%%s\n",
            dest, get_write_data_type(var_type), var_name);
    }
    return OK_OUTPUT;
}

/**
 * @brief Generate the right line of LLVM IR with the AST type.
 *        And give the value with a load.
 *
 * @param node          The AST node
 * @param f             The FILE to write in
 * @param type          This can be use to detect i32 or i8...
 *
 * @return The final variable.
 */
char *
llvm_gen_value(ast_node_t *node, FILE *f, data_types_t type, bool_t load_val)
{
    char *tmp = get_random_var_name();
    char *llvm_type = get_write_data_type(type);

    switch (node->_type) {
        case AST_LITERAL_INT:
            fprintf(f, "%%%s = add %s 0, %d\n", tmp, llvm_type,
                node->_ast_val._int_literal._value);
            break;
        case AST_LITERAL_FLOAT:
            fprintf(f, "%%%s = fadd %s %e, %e\n", tmp, llvm_type,
                    0.0f, node->_ast_val._float_literal._value);
            break;
        case AST_CALL_SYM:
            llvm_call_sym(node, f, tmp);
            break;
        case AST_SYMBOL:
            if (generate_symbol_from_param(node, f, &tmp) == OK_OUTPUT)
                break;
            fprintf(f, "%%%s = load %s, %s* %%%s\n", tmp,
                llvm_type, llvm_type, node->_ast_val._symbol._sym_name);
            break;
        case AST_BINARY_OP:
            llvm_math(node, f, tmp);
            break;
        case AST_STRING:
            llvm_string(node, f, tmp);
            break;
        case AST_CAST:
            llvm_cast(node, f, tmp);
            break;
        case AST_INDEX:
            llvm_index(node, f, tmp, load_val);
            break;
        case AST_FIELD:
            llvm_field(node, f, tmp, load_val);
            break;
        default:
            break;
    }
    return tmp;
}

/**
 * @brief Same as llvm_gen_value but give the address (ptr not the loaded val).
 *
 * @param node          The AST node
 * @param f             The FILE to write in
 *
 * @return The var name which is the ptr to the val.
 */
char *
llvm_gen_address(ast_node_t *node, FILE *f, bool_t need_load)
{
    data_types_t current_val_type = get_data_from_node(node->_ast_val._index._sym);
    char *current_tmp = llvm_gen_value(node->_ast_val._index._sym, f, current_val_type, FALSE);
    data_types_t idx_type = {0};
    data_types_t deref_type = {0};
    char *index_tmp = NULL;
    char *ptr_tmp = NULL;
    char *load_tmp = NULL;
    char *llvm_type = NULL;
    
    for (size_t i = 0; i < node->_ast_val._index._index_count; i++) {
        idx_type = get_data_from_node(node->_ast_val._index._indices[i]);
        deref_type = get_deref_data_type(current_val_type);
        index_tmp = llvm_gen_value(node->_ast_val._index._indices[i], f, idx_type, FALSE);
        ptr_tmp = get_random_var_name();
        llvm_type = get_write_data_type(deref_type); 
        fprintf(f, "%%%s = getelementptr inbounds %s, %s* %%%s, i32 %%%s\n",
            ptr_tmp, llvm_type, llvm_type, current_tmp, index_tmp);
        if (need_load && i < node->_ast_val._index._index_count - 1) {
            load_tmp = get_random_var_name();
            fprintf(f, "%%%s = load %s*, %s** %%%s\n",
                load_tmp, llvm_type, llvm_type, ptr_tmp);
            current_tmp = load_tmp;
        } else
            current_tmp = ptr_tmp;
        current_val_type = deref_type;
    }
    return current_tmp;
}
