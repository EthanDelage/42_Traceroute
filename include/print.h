#ifndef PRINT_H
#define PRINT_H

#include <netinet/in.h>


void print_traceroute_info(char *host, struct sockaddr_in *addr);
void print_hop(size_t hop);
void print_response_timeout();
void print_router(struct sockaddr_in *sock_addr);

#endif //PRINT_H
