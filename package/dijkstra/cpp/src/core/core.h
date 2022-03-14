#ifndef _CORE_H_
#define _CORE_H_

#include <iostream>
#include <cstdint>
#include <list>
#include <tuple>

namespace Core {
    class Graph {
        struct Node {
            bool visited;
            double distance;
            uint64_t prev;
            std::list<std::tuple<uint64_t, double> > neighbours;
        };
        uint64_t n_node, n_edge;
        double infinity;
        Node *adjacency_list;
    public:
        enum Err {
            FILE_ACCESS,
            IDX_OUT_OF_RANGE,
            NOT_CONNECTED
        };
        Graph(const char *fn);
        ~Graph();
        void log(std::ostream &os);
        double distance(uint64_t from, uint64_t to, bool verbose);
    };
}

#endif
