#include "core.h"

#include <stdlib.h>
#include <stdbool.h>

struct GraphNode {
    bool visited;
    double distance;
    uint64_t prev;
    struct List neighbors;
};

int graph_initialize(struct Graph *graph, const char *fn) {
    if (!graph || !fn) {
        return ERR_NULL_PTR;
    }
    FILE *fin = fopen(fn, "r");
    if (!fin) {
        return ERR_FILE_ACCESS;
    }
    fscanf(fin, "%lu %lu", &graph->n_node, &graph->n_edge);
    graph->adjacency_list = malloc(sizeof(struct GraphNode) * graph->n_node);
    struct GraphNode *iter = graph->adjacency_list;
    for (uint64_t i = 0; i < graph->n_node; ++i, ++iter) {
        list_initialize(&iter->neighbors);
    }
    double max = 0;
    for (uint64_t i = 0; i < graph->n_edge; ++i) {
        uint64_t from, to;
        double distance;
        fscanf(fin, "%lu %lu %lf",&from, &to, &distance);
        list_push(&graph->adjacency_list[from].neighbors, to, distance);
        list_push(&graph->adjacency_list[to].neighbors, from, distance);
        if (distance > max) {
            max = distance;
        }
    }
    fclose(fin);
    graph->infinity = max * (graph->n_edge + 1);
    return 0;
}

int graph_finalize(struct Graph *graph) {
    if (!graph) {
        return ERR_NULL_PTR;
    }
    struct GraphNode *iter = graph->adjacency_list;
    for (uint64_t i = 0; i < graph->n_node; ++i, ++iter) {
        list_finalize(&iter->neighbors);
    }
    free(graph->adjacency_list);
    return 0;
}

int graph_log(struct Graph *graph, FILE *fout) {
    if (!graph || !fout) {
        return ERR_NULL_PTR;
    }
    struct GraphNode *iter = graph->adjacency_list;
    for (uint64_t i = 0; i < graph->n_node; ++i, ++iter) {
        printf("Node %lu:\n", i);
        for (struct ListNode *j = iter->neighbors.head; j; j = j->next) {
            printf("To: %lu Distance: %lf\n", j->to, j->distance);
        }
    }
    return 0;
}
