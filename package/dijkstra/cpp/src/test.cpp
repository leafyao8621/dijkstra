#include "core/core.h"

int main() {
    try {
        Core::Graph graph("../../../graph/test.graph");
        graph.log(std::cout);
        std::cout << "Path:\n";
        double dist = graph.distance(0, 2, true);
        std::cout << "Distance: " << dist << '\n';
    } catch (Core::Graph::Err e) {
        switch (e) {
        case Core::Graph::Err::FILE_ACCESS:
            std::cout << "FILE_ACCESS\n";
            break;
        case Core::Graph::Err::IDX_OUT_OF_RANGE:
            std::cout << "IDX_OUT_OF_RANGE\n";
            break;
        case Core::Graph::Err::NOT_CONNECTED:
            std::cout << "NOT_CONNECTED\n";
            break;
        }
    }
    return 0;
}
