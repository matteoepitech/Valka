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
