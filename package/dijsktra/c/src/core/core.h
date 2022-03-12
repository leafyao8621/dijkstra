#ifndef _CORE_H_
#define _CORE_H_

#include "../util/util.h"

#define ERR_NULL_PTR 1
#define ERR_FILE_ACCESS 2
#define ERR_IDX_OUT_OF_RANGE 3
#define ERR_NOT_CONNECTED 4

struct Graph {
    uint64_t n_node, n_edge;
    double infinity;
    struct GraphNode *adjacency_list;
};

int graph_initialize(struct Graph *graph, const char *fn);
int graph_distance(struct Graph *graph, uint64_t from, uint64_t to);
int graph_finalize(struct Graph *graph);
int graph_log(struct Graph *graph, FILE *fout);

#endif
