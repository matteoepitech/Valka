/*
** VALKA PROJECT, 2025
** src/main
** File description:
** Valka var generator
*/

#include "valka.h"

/**
 * @brief Get a random var name used for temporary data.
 *
 * @return The var name.
 */
char *
get_random_var_name(void)
{
    int random_var_name_len = 16;
    char *name = MALLOC(sizeof(char) * random_var_name_len);

    sprintf(name, "var_%d", register_id);
    register_id++;
    return name;
}
