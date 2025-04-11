#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
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

