#ifndef SOCKET_H
#define SOCKET_H

#include "traceroute.h"

int init_icmp_socket();
int init_udp_socket();
void resolve_host(const char *host, traceroute_conf_t *conf);

#endif //SOCKET_H
