#include "print.h"

#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

void print_traceroute_info(traceroute_conf_t *conf) {
    printf("traceroute to %s (%s), %zu hops max, %zu byte packets\n", conf->opt.host, inet_ntoa(conf->send_packet.sock_addr.sin_addr), conf->opt.max_hops, conf->opt.packet_len);
}

void print_ttl(size_t ttl) {
    printf("%zu", ttl);
}

void print_response_timeout() {
    printf(" *");
    fflush(stdout);
}

void print_router(struct sockaddr_in *sock_addr) {
    char host[NI_MAXHOST];

    getnameinfo((struct sockaddr *)sock_addr, sizeof(*sock_addr), host, NI_MAXHOST, NULL, 0, 0);
    printf(" %s (%s)", host, inet_ntoa(sock_addr->sin_addr));
    fflush(stdout);
}

void print_trip_time(struct timeval send_tv, struct timeval recv_tv) {
    struct timeval  interval_tv;
    long interval;

    interval_tv.tv_sec = recv_tv.tv_sec - send_tv.tv_sec;
    interval_tv.tv_usec = recv_tv.tv_usec - send_tv.tv_usec;
    interval = interval_tv.tv_sec * 1000000 + interval_tv.tv_usec;
    if (interval < 0) {
        dprintf(STDERR_FILENO, "Warning: time of day goes back (%ldus), " \
                "taking countermeasures", interval);
        interval = 0;
    }
    printf(" %.3f ms", (float) interval / 1000);
    fflush(stdout);
}

