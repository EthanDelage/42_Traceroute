#include "udp.h"

#include <errno.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <netinet/udp.h>

static void fill_udp_header(struct udphdr *udphdr, uint16_t port, size_t data_len);
static void fill_udp_data(char *data, size_t len);

char *create_udp_packet(traceroute_conf_t *conf) {
    char *buffer;
    char *data;
    const size_t udp_packet_len = conf->opt.packet_len - sizeof(struct iphdr);
    const size_t data_len = udp_packet_len - sizeof(struct udphdr);

    buffer = conf->send_packet.buffer;
    data = buffer + sizeof(struct udphdr);
    fill_udp_header((struct udphdr *) buffer, conf->opt.port + conf->packet_send, data_len);
    fill_udp_data(data, data_len);
    return buffer;
}

static void fill_udp_header(struct udphdr *udphdr, uint16_t port, size_t data_len) {
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
