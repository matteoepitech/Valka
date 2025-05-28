/*
** VALKA PROJECT, 2025
** src/utils/strings/strndup
** File description:
** STRNDUP funciton
*/

#include "valka.h"

/**
 * @brief STRNDUP from valka.
 *
 * @param string        The original string
 * @param size          The size of the string
 *
 * @return The memory allocated string.
 */
char *
strndup_valka(const char *string, unsigned long size)
{
    char *result = NULL;

    if (string == NULL || size == 0)
        return NULL;
    result = MALLOC(sizeof(char) * (size + 1));
    for (unsigned long i = 0; i < size; i++) {
        result[i] = string[i];
    }
    return result;
}
