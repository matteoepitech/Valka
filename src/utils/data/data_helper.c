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
