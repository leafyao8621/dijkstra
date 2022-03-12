#include "core/core.h"

int main(void) {
    struct Graph graph;
    int ret = graph_initialize(&graph, "../../../graph/test.graph");
    if (ret) {
        goto finalize;
    }
    ret = graph_log(&graph, stdout);
    if (ret) {
        goto finalize;
    }
finalize:
    switch (ret) {
    case ERR_NULL_PTR:
        puts("NULL_PTR");
        break;
    case ERR_FILE_ACCESS:
        puts("FILE_ACCESS");
        break;
    case ERR_IDX_OUT_OF_RANGE:
        puts("IDX_OUT_OF_RANGE");
        break;
    case ERR_NOT_CONNECTED:
        puts("NOT_CONNECTED");
        break;
    }
    graph_finalize(&graph);
    return 0;
}
