#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdlib.h>
#include <stdint.h>

#define DEFAULT_PACKET_LEN 60
#define PACKET_MIN_LEN  28
#define DEFAULT_MAX_HOPS    30
#define DEFAULT_PROBES_PER_HOP  3
#define DEFAULT_FIRST_TTL   1
#define DEFAULT_PORT  33434

typedef struct traceroute_options_s {
    char *host;
    size_t packet_len;
    size_t max_hops;
    size_t probes_per_hop;
    int first_ttl;
    uint16_t port;
} traceroute_options_t;

void parse_opt(int argc, char **argv, traceroute_options_t *opt);

#endif //OPTIONS_H
