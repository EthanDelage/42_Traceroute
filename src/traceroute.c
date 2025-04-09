#include "traceroute.h"

#include <arpa/inet.h>
#include <stdio.h>

#include "socket.h"

void init_traceroute_conf(traceroute_conf_t *conf) {
    resolve_host(conf->opt.host, conf);
    printf("traceroute to %s (%s)\n", conf->opt.host, inet_ntoa(conf->sock_addr.sin_addr));
    conf->rcv_sock_fd = init_icmp_socket();
    conf->snd_sock_fd = init_udp_socket();
}
