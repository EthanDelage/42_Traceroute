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
    {0}
};

static error_t argp_parser(int key, char *arg, struct argp_state *state);

void parse_opt(int argc, char **argv, traceroute_options_t *opt) {
    struct argp argp = {options, argp_parser, args_doc, doc, 0, 0, 0};

    opt->max_hops = DEFAULT_MAX_HOPS;
    opt->probes_per_hop = DEFAULT_PROBES_PER_HOP;
    argp_parse(&argp, argc, argv, 0, NULL, opt);
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
        case ARGP_KEY_ARG:
            if (state->arg_num >= 1) {
                argp_error(state, "too many host operands");
            }
            opt->host = arg;
            break;
        case ARGP_KEY_NO_ARGS:
            argp_error(state, "missing host operand");
            // FALLTHROUGH
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}
