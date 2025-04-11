#ifndef PRINT_H
#define PRINT_H

#include <netinet/in.h>


void print_traceroute_info(char *host, struct sockaddr_in *addr);
void print_hop(size_t hop);
void print_response_timeout();
void print_router(struct sockaddr_in *sock_addr);
void print_trip_time(struct timeval send_tv, struct timeval recv_tv);

#endif //PRINT_H
