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
    if (token == NULL)
        return (data_types_t) {0};
    for (int i = 0; data_types[i]._id != 0; i++) {
        if (strncmp(&token->_start[1], data_types[i]._valka_ir,
            token->_length - 2) == 0 && 
            token->_length - 2 == strlen(data_types[i]._valka_ir)) {
            return data_types[i];
        }
    }
    return (data_types_t) {0};
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
    if (node->_type == AST_CALL_SYM)
        return get_prototype_from_name(node->_ast_val._call_sym._sym_name)._return;
    if (node->_type == AST_LITERAL_INT)
        return get_data_with_id(T_I32);
    if (node->_type == AST_SYMBOL)
        return get_sym_decl_from_name(node->_parent, node->_ast_val._call_sym._sym_name)->_ast_val._var_decl._var_type;
    if (node->_type == AST_STRING)
        return get_data_with_id(T_CHAR_P);
    if (node->_type == AST_BINARY_OP)
        return get_data_from_node(node->_ast_val._binary_op._left);
    if (node->_type == AST_CAST)
        return node->_ast_val._cast._cast_type;
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
