#include "options.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void parse_opt(int argc, char **argv, traceroute_options_t *opt) {
    if (argc != 2) {
        dprintf(STDERR_FILENO, "Need 1 arguments");
        exit(EXIT_FAILURE);
    }
    opt->host = argv[1];
}
