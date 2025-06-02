/*
** VALKA PROJECT, 2025
** src/utils/data/data_helper
** File description:
** Data helper functions
*/

#include "valka.h"

/**
 * @brief Get the data with ID.
 *
 * @param id            The ID
 *
 * @return The data.
 */
data_types_t
get_data_with_id(uint32_t id)
{
    for (int i = 0; data_types[i]._id != 0; i++) {
        if (data_types[i]._id == id)
            return data_types[i];
    }
    return (data_types_t) {0};
}

/**
 * @brief Get the token type of the data if the data is existing.
 *
 * @param token         The token
 */
data_types_t
get_data_type_from_token(token_t *token)
{
    int inside_len = token->_length - 2;
    char *inside = NULL;
    int ptr_level = 0;
    
    if (token == NULL || token->_length < 3) 
        return (data_types_t){0};
    inside = strndup_valka(&token->_start[1], inside_len);
    for (int i = inside_len - 1; i >= 0 && inside[i] == '*'; i--) {
        ptr_level++;
        inside[i] = '\0';
        inside_len--;
    }
    for (int i = 0; data_types[i]._id != 0; i++) {
        if (strcmp(inside, data_types[i]._valka_ir) == 0) {
            data_types_t result = data_types[i];
            result._ptr_level = ptr_level;
            return result;
        }
    }

    if (strncmp("struct ", inside, 7) == 0) {
        data_types_t result = {0};
        result._bits_sz = 0;
        result._id = T_STRUCT;
        char *struct_name = inside + 7;
        strncpy(result._valka_ir, inside, sizeof(result._valka_ir) - 1);
        result._valka_ir[sizeof(result._valka_ir) - 1] = '\0';
        snprintf(result._llvm_ir, sizeof(result._llvm_ir), "%%%s", struct_name);
        result._ptr_level = ptr_level;
        return result;
    }
    return (data_types_t){0};
}

/**
 * @brief Get the right type using only the AST node.
 *
 * @param node          The AST node
 *
 * @return The data type.
 */
data_types_t
get_data_from_node(ast_node_t *node)
{
    data_types_t tmp = {0};

    if (node->_type == AST_CALL_SYM)
        return get_prototype_from_name(node->_ast_val._call_sym._sym_name)._return;
    if (node->_type == AST_LITERAL_INT)
        return get_data_with_id(T_I32);
    if (node->_type == AST_LITERAL_FLOAT)
        return get_data_with_id(T_FLOAT);
    if (node->_type == AST_SYMBOL)
        return get_sym_decl_from_name(node->_parent, node->_ast_val._call_sym._sym_name)->_ast_val._var_decl._var_type;
    if (node->_type == AST_STRING) {
        tmp = get_data_with_id(T_CHAR);
        tmp._ptr_level++;
        return tmp;
    }
    if (node->_type == AST_BINARY_OP)
        return get_data_from_node(node->_ast_val._binary_op._left);
    if (node->_type == AST_CAST)
        return node->_ast_val._cast._cast_type;
    if (node->_type == AST_INDEX) {
        tmp = get_data_from_node(node->_ast_val._index._sym);
        tmp._ptr_level -= node->_ast_val._index._index_count;
        return tmp;
    }
    PERROR("This type is not handled yet!");
    return (data_types_t) {0};
}

/**
 * @brief Get the highest data type between 2.
 *
 * @param d1            data type 1
 * @param d2            data type 2
 *
 * @return The highest data type.
 */
data_types_t
get_highest_data_type(data_types_t d1, data_types_t d2)
{
    if (d1._bits_sz >= d2._bits_sz)
        return d1;
    return d2;
}

/**
 * @brief Get the data type with dereferencing.
 *
 * @param data          The data type
 *
 * @return The deref data type.
 */
data_types_t
get_deref_data_type(data_types_t data)
{
    data_types_t deref_data = data;

    deref_data._ptr_level--;
    if (deref_data._ptr_level < 0)
        deref_data._ptr_level = 0;
    return deref_data;
}

/**
 * @brief Get the final type with pointer level.
 *
 * @param data          The data
 *
 * @return The type.
 */
char *
get_write_data_type(data_types_t data)
{
    uint32_t base_len = strlen(data._llvm_ir);
    uint32_t total_len = base_len + data._ptr_level + 1;

    char *result = MALLOC(total_len);
    strcpy(result, data._llvm_ir);
    for (int32_t i = 0; i < data._ptr_level; i++) {
        result[base_len + i] = '*';
    }
    result[total_len - 1] = '\0';
    return result;
}
