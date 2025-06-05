/*
** VALKA PROJECT, 2025
** src/utils/strings/strdup
** File description:
** STRDUP funciton
*/

#include "valka.h"

/**
 * @brief STRDUP from valka.
 *
 * @param string        The original string
 *
 * @return The memory allocated string.
 */
char *
strdup_valka(const char *string)
{
    unsigned long size = strlen(string);
    char *result = NULL;

    if (string == NULL)
        return NULL;
    result = MALLOC(sizeof(char) * (size + 1));
    for (unsigned long i = 0; i < size; i++) {
        result[i] = string[i];
    }
    return result;
}
