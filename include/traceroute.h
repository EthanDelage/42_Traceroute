#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <netinet/in.h>
#include <sys/time.h>

#include "options.h"

#define MAX_ICMP_PACKET_SIZE    1024

typedef struct traceroute_recv_packet_s {
    char *buffer;
    ssize_t packet_size;
    struct sockaddr_in sock_addr;
    struct sockaddr_in *prev_sock_addr;
    struct timeval tv;
} traceroute_recv_packet_t;

typedef struct traceroute_send_packet_s {
    char *buffer;
    size_t buffer_size;
    struct sockaddr_in sock_addr;
    struct timeval tv;
} traceroute_send_packet_t;

typedef struct traceroute_conf_s {
    int snd_sock_fd;
    int rcv_sock_fd;

    traceroute_options_t opt;
    size_t packet_send;
    traceroute_send_packet_t send_packet;
    traceroute_recv_packet_t recv_packet;
} traceroute_conf_t;

void init_traceroute_conf(traceroute_conf_t *conf);
void free_traceroute_conf(traceroute_conf_t *conf);
void run_traceroute(traceroute_conf_t *conf);

#endif //TRACEROUTE_H
