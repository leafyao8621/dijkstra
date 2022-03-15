#include "core.h"
#include "../util/mt19937.h"

#include <stdlib.h>

#define ERR_TOO_MANY_EDGES 1
#define ERR_INVALID_SEED 2
#define ERR_FILE_ACCESS 3

int core_generate(
    uint64_t n_node,
    uint64_t n_edge,
    double max_distance,
    uint32_t seed,
    const char *ofn
) {
    uint64_t max_edge = n_node * n_node;
    if (n_edge >= (max_edge >> 1)) {
        return ERR_TOO_MANY_EDGES;
    }
    if (!seed) {
        return ERR_INVALID_SEED;
    }
    struct MT19937 gen;
    mt19937_initialize(&gen, seed);
    uint8_t *adjacency_matrix = 0;
    adjacency_matrix = calloc(max_edge, 1);
    FILE *fout = 0;
    fout = fopen(ofn, "w");
    int ret = 0;
    if (!fout) {
        ret = ERR_FILE_ACCESS;
        goto cleanup;
    }
    fprintf(fout, "%lu %lu\n", n_node, n_edge);
    for (uint64_t i = 0; i < n_edge; ++i) {
        uint64_t from, to;
        for (
            from = mt19937_gen(&gen) % (n_node - 1),
            to =
                from == n_node - 2 ?
                n_node - 1 :
                mt19937_gen(&gen) % (n_node - from - 2) + from + 1;
            adjacency_matrix[from * n_node + to];
            from = mt19937_gen(&gen) % (n_node - 1),
            to =
                from == n_node - 2 ?
                n_node - 1 :
                mt19937_gen(&gen) % (n_node - from - 2) + from + 1
        );
        adjacency_matrix[from * n_node + to] = 1;
        adjacency_matrix[to * n_node + from] = 1;
        double distance =\
            (mt19937_gen(&gen) / (double)0xffffffff) * max_distance;
        fprintf(fout, "%lu %lu %lf\n", from, to, distance);
    }
cleanup:
    if (adjacency_matrix) {
        free(adjacency_matrix);
    }
    if (fout) {
        fclose(fout);
    }
    return ret;
}
