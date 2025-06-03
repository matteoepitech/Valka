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
get_write_data_type(data_types_t data, bool_t only_primitive)
{
    char *result;
    uint32_t pos = 0;
    uint32_t total_len = 0;
    
    if (only_primitive == TRUE)
        return strdup(data._llvm_ir);
    if (data._array_count > 0) {
        for (uint32_t i = 0; i < data._array_count; i++) {
            total_len += snprintf(NULL, 0, "[%d x ", data._array_dims[i]);
        }
        total_len += strlen(data._llvm_ir) + data._ptr_level + data._array_count + 1;
    } else {
        total_len = strlen(data._llvm_ir) + data._ptr_level + 1;
    }
    result = MALLOC(total_len);
    for (uint32_t i = 0; i < data._array_count; i++) {
        pos += sprintf(&result[pos], "[%d x ", data._array_dims[i]);
    }
    strcpy(&result[pos], data._llvm_ir);
    pos += strlen(data._llvm_ir);
    for (int i = 0; i < data._ptr_level; i++) {
        result[pos++] = '*';
    }
    for (uint32_t i = 0; i < data._array_count; i++) {
        result[pos++] = ']';
    }
    result[pos] = '\0';
    return result;
}

/**
 * @brief Get the type of the first element in a array.
 *
 * @param array_type    The type of the array
 *
 * @return The data type of the first element.
 */
data_types_t
get_array_elem_data(data_types_t array_type)
{
    data_types_t elem_type = array_type;
    
    if (array_type._array_count == 0) {
        return array_type;
    }
    if (array_type._array_count == 1) {
        elem_type._array_count = 0;
    } else {
        elem_type._array_count = array_type._array_count - 1;
        for (uint32_t i = 0; i < elem_type._array_count; i++) {
            elem_type._array_dims[i] = array_type._array_dims[i + 1];
        }
    }
    return elem_type;
}
