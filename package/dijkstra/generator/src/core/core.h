#ifndef _CORE_H_
#define _CORE_H_

#include <stdio.h>
#include <stdint.h>

#define ERR_TOO_MANY_EDGES 1
#define ERR_INVALID_SEED 2
#define ERR_FILE_ACCESS 3

int core_generate(
    uint64_t n_node,
    uint64_t n_edge,
    double max_distance,
    uint32_t seed,
    const char *ofn
);

#endif
