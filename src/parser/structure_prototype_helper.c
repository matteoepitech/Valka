/*
** VALKA PROJECT, 2025
** src/parser/structure_prototype_helper
** File description:
** Handle structure prototypes
*/

#include "valka.h"

// @INFO this function use the extern variables defined in main.c
/**
 * @brief Add a structure prototype.
 *
 * @param struct_node     The AST node
 */
void
add_structure_prototype(ast_node_t *struct_node)
{
    structs_prototype_t *new_proto = NULL;
    uint32_t new_count = 0;

    if (struct_node == NULL || struct_node->_type != AST_STRUCT)
        return;
    new_count = structures_count + 1;
    structures_prototype = REALLOC(structures_prototype, sizeof(structs_prototype_t) * new_count);
    new_proto = &structures_prototype[structures_count];
    new_proto->_struct_name = strdup(struct_node->_ast_val._struct._struct_name);
    new_proto->_fields = struct_node->_ast_val._struct._fields;
    new_proto->_fields_count = struct_node->_ast_val._struct._fields_count;
    structures_count = new_count;
}

/**
 * @brief Get a prototype from name.
 *
 * @param struct_name     The structure name
 *
 * @return The prototype.
 */
structs_prototype_t
get_struct_prototype_from_name(const char *struct_name)
{
    for (uint32_t i = 0; i < structures_count; i++) {
        if (strcmp(structures_prototype[i]._struct_name, struct_name) == 0)
            return structures_prototype[i];
    }
    return (structs_prototype_t){0};
}
