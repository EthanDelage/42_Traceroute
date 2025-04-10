#include "udp.h"

#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/udp.h>

static void fill_udp_header(struct udphdr *udphdr, u_short port, size_t data_len);
static void fill_udp_data(char *data, size_t len);

char *create_udp_packet(traceroute_conf_t *conf) {
    char *buffer;
    char *data;
    const size_t udp_packet_len = DEFAULT_PACKET_SIZE - sizeof(struct iphdr);
    const size_t data_len = udp_packet_len - sizeof(struct udphdr);

    buffer = malloc(udp_packet_len);
    if (buffer == NULL) {
        perror("malloc");
        exit(errno);
    }
    fill_udp_header((struct udphdr *) buffer, DEFAULT_PORT + conf->packet_send, data_len);
    data = buffer + sizeof(struct udphdr);
    fill_udp_data(data, data_len);
    return buffer;
}

static void fill_udp_header(struct udphdr *udphdr, u_short port, size_t data_len) {
    udphdr->uh_sport = htons(33434); // TODO: change src port
    udphdr->uh_dport = htons(port);
    udphdr->uh_ulen = htons(sizeof(struct udphdr) + data_len);
    udphdr->uh_sum = 0; // OS compute it
}

static void fill_udp_data(char *data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        data[i] = '@' + i % (127 + 1 - '@'); // 127 is equal to DEL
    }
}
