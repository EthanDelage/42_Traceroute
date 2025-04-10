#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <netinet/in.h>

#include "options.h"

#define DEFAULT_MAX_HOPS    30
#define DEFAULT_PROBES_PER_HOP  3

typedef struct traceroute_conf_s {
    int snd_sock_fd;
    int rcv_sock_fd;
    struct sockaddr_in sock_addr;

    traceroute_options_t opt;
    size_t packet_send;
} traceroute_conf_t;

void init_traceroute_conf(traceroute_conf_t *conf);
void run_traceroute(traceroute_conf_t *conf);

#endif //TRACEROUTE_H
