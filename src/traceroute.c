#include "print.h"
#include "traceroute.h"
#include "socket.h"
#include "udp.h"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>

static void execute_hop(traceroute_conf_t *conf, int hop);
static void send_probe(traceroute_conf_t *conf);
static void receive_response(traceroute_conf_t *conf);
static void process_response(traceroute_conf_t *conf);

void init_traceroute_conf(traceroute_conf_t *conf) {
    const size_t udp_packet_len = DEFAULT_PACKET_SIZE - sizeof(struct iphdr);

    resolve_host(conf->opt.host, conf);
    print_traceroute_info(conf->opt.host, &conf->send_packet.sock_addr);
    conf->rcv_sock_fd = init_icmp_socket();
    conf->snd_sock_fd = init_udp_socket();
    conf->send_packet.buffer_size = udp_packet_len;
    conf->send_packet.buffer = malloc(udp_packet_len);
    conf->recv_packet.buffer = malloc(MAX_ICMP_PACKET_SIZE);
    if (conf->send_packet.buffer == NULL || conf->recv_packet.buffer == NULL) {
        free_traceroute_conf(conf);
        perror("malloc");
        exit(errno);
    }
}

void free_traceroute_conf(traceroute_conf_t *conf) {
    free(conf->send_packet.buffer);
    free(conf->recv_packet.buffer);
}

void run_traceroute(traceroute_conf_t *conf) {
    int stop = 0;
    int hop = 1;

    while (!stop && hop < DEFAULT_MAX_HOPS + 1) {
        set_sockopt_ttl(conf->snd_sock_fd, hop);
        execute_hop(conf, hop);
        hop++;
    }
}

/**
 * @brief Executes the probe sequence for a given hop (TTL).
 *
 * This function sends a series of probes (usually 3) with the given TTL
 * to the current hop, waits for ICMP responses, and processes the results
 * for each probe. It is used to determine the path to the destination
 * by sending probes with incremented TTL values.
 *
 * @param conf Pointer to the traceroute configuration structure.
 * @param hop The current hop (TTL) for which probes are sent.
 * @return void
 * @note This function handles multiple probes (typically 3) for a given hop.
 *       If no response is received, it displays `* * *`. If a response is
 *       received, it processes and prints the results for that hop.
 */
static void execute_hop(traceroute_conf_t *conf, int hop) {
    print_hop(hop);
    for (int i = 0; i < DEFAULT_PROBES_PER_HOP; i++) {
        send_probe(conf);
        receive_response(conf);
        if (conf->recv_packet.packet_size == -1) {
            print_response_timeout();
            fflush(stdout);
        } else {
            process_response(conf);
        }
    }
    printf("\n");
}

static void send_probe(traceroute_conf_t *conf) {
    char *buffer = create_udp_packet(conf);

    struct sockaddr_in dest;
    dest.sin_family = AF_INET;
    dest.sin_port = ((struct udphdr *)buffer)->uh_dport;
    dest.sin_addr.s_addr = conf->send_packet.sock_addr.sin_addr.s_addr;

    if (sendto(conf->snd_sock_fd, buffer, ntohs(((struct udphdr *)buffer)->uh_ulen), 0,
        (struct sockaddr *)&dest, sizeof(dest)) < 0) {
        perror("sendto");
        free_traceroute_conf(conf);
        exit(errno);
    }
    conf->packet_send++;
}

static void receive_response(traceroute_conf_t *conf) {
    socklen_t len = sizeof(conf->recv_packet.sock_addr);
    ssize_t ret;

    ret = recvfrom(conf->rcv_sock_fd, conf->recv_packet.buffer, MAX_ICMP_PACKET_SIZE, 0, (struct sockaddr *)&conf->recv_packet.sock_addr, &len);
    conf->recv_packet.packet_size = ret;
}

static void process_response(traceroute_conf_t *conf) {
    struct icmphdr *icmp_hdr;

    icmp_hdr = (struct icmphdr *)(conf->recv_packet.buffer + sizeof(struct iphdr));
    (void) icmp_hdr;
    print_router(&conf->recv_packet.sock_addr);
}
