#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct traceroute_options_s {
    char *host;
} traceroute_options_t;

void parse_opt(int argc, char **argv, traceroute_options_t *opt);

#endif //OPTIONS_H
