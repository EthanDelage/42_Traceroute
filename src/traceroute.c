#include "traceroute.h"
#include "socket.h"
#include "udp.h"

#include <arpa/inet.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>

static void send_probes_burst(traceroute_conf_t *conf);
static void send_probe(traceroute_conf_t *conf);

void init_traceroute_conf(traceroute_conf_t *conf) {
    resolve_host(conf->opt.host, conf);
    printf("traceroute to %s (%s)\n", conf->opt.host, inet_ntoa(conf->sock_addr.sin_addr));
    conf->rcv_sock_fd = init_icmp_socket();
    conf->snd_sock_fd = init_udp_socket();
}

void run_traceroute(traceroute_conf_t *conf) {
    int stop = 0;
    int hop = 1;

    while (!stop && hop < DEFAULT_MAX_HOPS + 1) {
        set_sockopt_ttl(conf->snd_sock_fd, hop);
        send_probes_burst(conf);
        hop++;
    }
}

static void send_probes_burst(traceroute_conf_t *conf) {
    for (int i = 0; i < DEFAULT_PROBES_PER_HOP; i++) {
        send_probe(conf);
    }
}

static void send_probe(traceroute_conf_t *conf) {
    char *buffer = create_udp_packet(conf);

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = ((struct udphdr *)buffer)->uh_dport;
    dest.sin_addr.s_addr = conf->sock_addr.sin_addr.s_addr;

    sendto(conf->snd_sock_fd, buffer, ntohs(((struct udphdr *)buffer)->uh_ulen), 0,
        (struct sockaddr *)&dest, sizeof(dest));
    free(buffer);
    conf->packet_send++;
}
