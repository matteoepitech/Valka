/*
** VALKA PROJECT, 2025
** src/core/llvm/data_node
** File description:
** Get data types from AST nodes
*/

#include "valka.h"

/**
 * @brief Get data type from field node.
 *
 * @param node          The AST field node
 *
 * @return The data type of the field.
 */
static data_types_t
get_data_from_field(ast_node_t *node)
{
    data_types_t parent_type = get_data_from_node(node->_ast_val._field._symbol);
    char *struct_name = get_write_data_type(parent_type, FALSE);
    structs_prototype_t structure = get_struct_prototype_from_name(struct_name);
    uint32_t field_idx = get_struct_field_index(structure, node->_ast_val._field._field_name);
    
    return structure._fields[field_idx]->_ast_val._var_decl._var_type;
}

/**
 * @brief Get data type from symbol node.
 *
 * @param node          The AST symbol node
 *
 * @return The data type of the symbol.
 */
static data_types_t
get_data_from_symbol(ast_node_t *node)
{
    return get_sym_decl_from_name(node->_parent, node->_ast_val._symbol._sym_name)->_ast_val._var_decl._var_type;
}

/**
 * @brief Get data type from call symbol node.
 *
 * @param node          The AST call symbol node
 *
 * @return The return data type of the function.
 */
static data_types_t
get_data_from_call_sym(ast_node_t *node)
{
    return get_prototype_from_name(node->_ast_val._call_sym._sym_name)._return;
}

/**
 * @brief Get data type from literal nodes.
 *
 * @param node          The AST literal node
 *
 * @return The data type of the literal.
 */
static data_types_t
get_data_from_literal(ast_node_t *node)
{
    data_types_t tmp = {0};

    if (node->_type == AST_LITERAL_INT)
        return get_data_with_id(T_I32);
    if (node->_type == AST_LITERAL_FLOAT)
        return get_data_with_id(T_FLOAT);
    tmp = get_data_with_id(T_CHAR);
    tmp._ptr_level++;
    return tmp;
}

/**
 * @brief Get data type from binary operation node.
 *
 * @param node          The AST binary operation node
 *
 * @return The data type of the left operand.
 */
static data_types_t
get_data_from_binary_op(ast_node_t *node)
{
    return get_data_from_node(node->_ast_val._binary_op._left);
}

/**
 * @brief Get data type from cast node.
 *
 * @param node          The AST cast node
 *
 * @return The cast target data type.
 */
static data_types_t
get_data_from_cast(ast_node_t *node)
{
    return node->_ast_val._cast._cast_type;
}

/**
 * @brief Get data type from index node.
 *
 * @param node          The AST index node
 *
 * @return The dereferenced data type.
 */
static data_types_t
get_data_from_index(ast_node_t *node)
{
    data_types_t tmp = get_data_from_node(node->_ast_val._index._sym);

    tmp._ptr_level -= node->_ast_val._index._index_count;
    return tmp;
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
    switch (node->_type) {
        case AST_FIELD:
            return get_data_from_field(node);
        case AST_CALL_SYM:
            return get_data_from_call_sym(node);
        case AST_LITERAL_INT:
        case AST_LITERAL_FLOAT:
        case AST_STRING:
            return get_data_from_literal(node);
        case AST_SYMBOL:
            return get_data_from_symbol(node);
        case AST_BINARY_OP:
            return get_data_from_binary_op(node);
        case AST_CAST:
            return get_data_from_cast(node);
        case AST_INDEX:
            return get_data_from_index(node);
        default:
            PERROR("This type is not handled yet!");
            return (data_types_t) {0};
    }
}
