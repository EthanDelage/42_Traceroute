#ifndef SOCKET_H
#define SOCKET_H

#include "traceroute.h"

int init_icmp_socket(traceroute_conf_t *conf);
int init_udp_socket();
void set_sockopt_ttl(int sock_fd, int ttl);
void resolve_host(const char *host, traceroute_conf_t *conf);

#endif //SOCKET_H
