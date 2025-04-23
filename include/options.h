#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdlib.h>
#include <stdint.h>

#define DEFAULT_PACKET_LEN 60
#define MIN_PACKET_LEN  28
#define MAX_PACKET_LEN 65000
#define DEFAULT_MAX_HOPS    30
#define MAX_HOPS    255
#define DEFAULT_PROBES_PER_HOP  3
#define MAX_PROBES_PER_HOP    10
#define DEFAULT_FIRST_TTL   1
#define DEFAULT_PORT  33434
#define MAX_PORT      65535
#define DEFAULT_RECV_TIMEOUT_SEC    5
#define MAX_RECV_TIMEOUT_SEC    60


typedef struct traceroute_options_s {
    char *host;
    size_t packet_len;
    size_t max_hops;
    size_t probes_per_hop;
    size_t first_ttl;
    uint16_t port;
    struct timeval recv_timeout;
} traceroute_options_t;

void parse_opt(int argc, char **argv, traceroute_options_t *opt);

#endif //OPTIONS_H
