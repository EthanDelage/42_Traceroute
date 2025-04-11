#include <stdio.h>
#include <arpa/inet.h>

void print_traceroute_info(char *host, struct sockaddr_in *addr) {
    printf("traceroute to %s (%s)\n", host, inet_ntoa(addr->sin_addr));
}

void print_hop(size_t hop) {
    printf("%zu", hop);
}

void print_response_timeout() {
    printf(" *");
    fflush(stdout);
}

void print_router(struct sockaddr_in *sock_addr) {
    printf(" %s", inet_ntoa(sock_addr->sin_addr));
}
