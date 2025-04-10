#ifndef UDP_H
#define UDP_H

#include "traceroute.h"

#define DEFAULT_PORT  33434
#define DEFAULT_PACKET_SIZE 60

char *create_udp_packet(traceroute_conf_t *conf);

#endif //UDP_H
