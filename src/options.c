#include "options.h"

#include <argp.h>
#include <stdio.h>
#include <unistd.h>

#include "common.h"

const char *args_doc = "host [packet_len]";
const char *doc = "print the route packets trace to network host";

static struct argp_option options[] = {
    {"max-hop", 'm', "max_ttl", 0, "Set the max number of hops (max TTL to be reached). Default is 30", 0},
    {"queries", 'q', "nqueries", 0, "Set the number of probes per each hop. Default is 3", 0},
    {"first", 'f', "first_ttl", 0, "Start from the first_ttl hop (instead from 1)", 0},
    {"port", 'p', "port", 0, "Set the destination port to use (incremented by each probe, default is 33434)", 0},
    {"wait", 'w', "MAX", 0, "Wait for a probe no more than MAX (default 5.0) seconds", 0},
    {0}
};

static error_t argp_parser(int key, char *arg, struct argp_state *state);

void parse_opt(int argc, char **argv, traceroute_options_t *opt) {
    struct argp argp = {options, argp_parser, args_doc, doc, 0, 0, 0};

    opt->packet_len = DEFAULT_PACKET_LEN;
    opt->max_hops = DEFAULT_MAX_HOPS;
    opt->probes_per_hop = DEFAULT_PROBES_PER_HOP;
    opt->first_ttl = DEFAULT_FIRST_TTL;
    opt->port = DEFAULT_PORT;
    opt->recv_timeout.tv_sec = DEFAULT_RECV_TIMEOUT_SEC;
    argp_parse(&argp, argc, argv, 0, NULL, opt);
    if (opt->packet_len < PACKET_MIN_LEN) {
        opt->packet_len = PACKET_MIN_LEN;
    }
    if (opt->recv_timeout.tv_sec == 0 && opt->recv_timeout.tv_usec == 0) {
        opt->recv_timeout.tv_usec = 1;
    } else if (opt->recv_timeout.tv_sec >= 60) {
        opt->recv_timeout.tv_sec = MAX_RECV_TIMEOUT_SEC;
        opt->recv_timeout.tv_usec = 0;
    }
}

static error_t argp_parser(int key, char *arg, struct argp_state *state) {
    traceroute_options_t *opt = state->input;

    switch (key) {
        case 'm':
            opt->max_hops = convert_arg_to_size_t(arg, 255, 0);
            break;
        case 'q':
            opt->probes_per_hop = convert_arg_to_size_t(arg, 10, 0);
            break;
        case 'f':
            opt->first_ttl = (int) convert_arg_to_size_t(arg, 30, 0);
            break;
        case 'p':
            opt->port = convert_arg_to_size_t(arg, 65535, 0);
            break;
        case 'w':
            opt->recv_timeout = convert_double_to_timeval(convert_arg_to_double(arg));
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num == 0) {
                opt->host = arg;
            } else if (state->arg_num == 1) {
                opt->packet_len = convert_arg_to_size_t(arg, 65000, 1);
            } else {
                argp_error(state, "too many args");
            }
            break;
        case ARGP_KEY_NO_ARGS:
            argp_error(state, "missing host operand");
            // FALLTHROUGH
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
