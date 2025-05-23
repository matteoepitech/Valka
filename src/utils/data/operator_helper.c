/*
** VALKA PROJECT, 2025
** src/utils/data/operator_helper
** File description:
** Operator helper functions
*/

#include "valka.h"

/**
 * @brief Get the operator data with a char.
 *
 * @param char           The char
 *
 * @return The data.
 */
bin_ope_t
get_operator_with_char(char op)
{
    for (int i = 0; bin_operations[i]._operator != 0; i++) {
        if (bin_operations[i]._operator == op)
            return bin_operations[i];
    }
    return (bin_ope_t) {0};
}
