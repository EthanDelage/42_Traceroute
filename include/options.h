#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdlib.h>

#define DEFAULT_MAX_HOPS    30
#define DEFAULT_PROBES_PER_HOP  3

typedef struct traceroute_options_s {
    char *host;
    size_t max_hops;
    size_t probes_per_hop;
} traceroute_options_t;

void parse_opt(int argc, char **argv, traceroute_options_t *opt);

#endif //OPTIONS_H
