#include "socket.h"

#include <err.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/errno.h>

int init_icmp_socket() {
    int sock_fd;

    sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock_fd < 0) {
        err(errno, "icmp socket");
    }
    return sock_fd;
}

int init_udp_socket() {
    int sock_fd;

    sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sock_fd < 0) {
        err(errno, "raw socket");
    }
    return sock_fd;
}

void set_sockopt_ttl(int sock_fd, int ttl) {
    if (setsockopt(sock_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
        perror("setsockopt IP_TTL");
        exit(EXIT_FAILURE);
    }
}

void resolve_host(const char *host, traceroute_conf_t *conf) {
    struct addrinfo hints = {0};
    struct addrinfo *res;
    int status;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    status = getaddrinfo(host, NULL, &hints, &res);
    if (status != 0) {
        dprintf(STDERR_FILENO, "%s Name or service not known\n", conf->opt.host);
        exit(2);
    }
    conf->sock_addr = *(struct sockaddr_in *)res->ai_addr;
    freeaddrinfo(res);
}
