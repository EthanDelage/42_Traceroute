#include "common.h"

#include <error.h>

/**
 * @brief convert a string to a size_t
 * @param arg string to convert
 * @param max maximum value, if max = 0, there is no maximum value
 * @param allow_zero if true, check value != 0
 * @return result of the conversion
 */
size_t convert_arg_to_size_t(char *arg, size_t max, int allow_zero) {
    char *end;
    unsigned long value;

    value = strtoul(arg, &end, 0);
    if (*end) {
        error(EXIT_FAILURE, 0, "invalid value (`%s' near `%s')", arg, end);
    }
    if (value == 0 && !allow_zero) {
        error(EXIT_FAILURE, 0, "option value too small: %s", arg);
    }
    if (max && value > max) {
        error(EXIT_FAILURE, 0, "option value too big: %s", arg);
    }
    return value;
}
