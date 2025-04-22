#include "common.h"

#include <error.h>
#include <math.h>
#include <sys/time.h>

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

/**
 * @brief convert a string to a double
 * @param arg string to convert
 * @return result of the conversion
 */
double convert_arg_to_double(char *arg) {
    char *end;
    double value;

    value = strtod(arg, &end);
    if (*end) {
        error(EXIT_FAILURE, 0, "invalid value (`%s' near `%s')", arg, end);
    }
    return value;
}

/**
 * @brief convert double value (in seconds) into struct timeval
 * @param seconds value to convert (in seconds)
 * @return value converted as struct timeval
 */
struct timeval convert_double_to_timeval(double seconds) {
    double integral_part;
    double fractional_part;
    struct timeval result;

    fractional_part = modf(seconds, &integral_part);
    result.tv_sec = (time_t) integral_part;
    result.tv_usec = (suseconds_t)(fractional_part * 1e6);

    if (result.tv_usec >= 1000000) {
        result.tv_sec++;
        result.tv_usec -= 1000000;
    }
    return result;
}
