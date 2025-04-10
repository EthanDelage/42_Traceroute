#include "traceroute.h"
#include "socket.h"
#include "udp.h"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

static void execute_hop(traceroute_conf_t *conf, int hop);
static void send_probe(traceroute_conf_t *conf);
static traceroute_response_t receive_response(traceroute_conf_t *conf);
static void process_response(traceroute_response_t response);

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
    traceroute_response_t response;

    printf("%d", hop);
    for (int i = 0; i < DEFAULT_PROBES_PER_HOP; i++) {
        send_probe(conf);
        response = receive_response(conf);
        if (response.packet_size == -1) {
            printf(" *");
            fflush(stdout);
        } else {
            process_response(response);
        }
        free(response.buffer);
    }
    printf("\n");
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

static traceroute_response_t receive_response(traceroute_conf_t *conf) {
    traceroute_response_t response = {0};
    char *buffer;
    socklen_t len = sizeof(response.sock_addr);
    ssize_t ret;

    buffer = malloc(MAX_ICMP_PACKET_SIZE);
    if (buffer == NULL) {
        perror("malloc");
        exit(errno);
    }
    ret = recvfrom(conf->rcv_sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&response.sock_addr, &len);
    response.buffer = buffer;
    response.packet_size = ret;
    return response;
}

static void process_response(traceroute_response_t response) {
    struct icmphdr *icmp_hdr;

    icmp_hdr = (struct icmphdr *)(response.buffer + sizeof(struct iphdr));
    (void) icmp_hdr;
    printf(" %s", inet_ntoa(response.sock_addr.sin_addr));
    fflush(stdout);
}
