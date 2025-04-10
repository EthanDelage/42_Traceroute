#include <stdlib.h>

#include "options.h"
#include "traceroute.h"

int main(int argc, char **argv) {
    traceroute_conf_t conf = {0};
    parse_opt(argc, argv, &conf.opt);
    init_traceroute_conf(&conf);
    run_traceroute(&conf);
    return EXIT_SUCCESS;
}