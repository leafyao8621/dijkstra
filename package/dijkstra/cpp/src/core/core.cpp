#include "core.h"

#include <fstream>
#include <vector>
#include <algorithm>

Core::Graph::Graph(const char *fn) {
    std::ifstream ifs(fn);
    if (ifs.fail()) {
        throw Core::Graph::Err::FILE_ACCESS;
    }
    ifs >> this->n_node >> this->n_edge;
    this->adjacency_list = new Core::Graph::Node[this->n_node];
    double max = 0;
    for (uint64_t i = 0; i < this->n_edge; ++i) {
        uint64_t from, to;
        double distance;
        ifs >> from >> to >> distance;
        if (distance > max) {
            max = distance;
        }
        this->adjacency_list[from]
            .neighbours
            .push_back(std::make_tuple(to, distance));
        this->adjacency_list[to]
            .neighbours
            .push_back(std::make_tuple(from, distance));
    }
    this->infinity = (this->n_edge + 1) * max;
}

Core::Graph::~Graph() {
    delete[] this->adjacency_list;
}

void Core::Graph::log(std::ostream &os) {
    Core::Graph::Node *iter = this->adjacency_list;
    for (uint64_t i = 0; i < this->n_node; ++i, ++iter) {
        os << "Node " << i << ":\n";
        for (const auto &j : iter->neighbours) {
            os << "To: " << std::get<0>(j) <<
            " Distance: " << std::get<1>(j) << '\n';
        }
    }
}

double Core::Graph::distance(uint64_t from, uint64_t to, bool verbose) {
    if (from >= this->n_node || to >= this->n_node) {
        throw Core::Graph::Err::IDX_OUT_OF_RANGE;
    }
    std::vector<std::tuple<double, uint64_t> > pq;
    Node *iter_al = this->adjacency_list;
    for (uint64_t i = 0; i < this->n_node; ++i, ++iter_al) {
        iter_al->distance = this->infinity;
        iter_al->visited = false;
        pq.push_back(std::make_tuple(i == from ? 0 : -this->infinity, i));
        std::push_heap(pq.begin(), pq.end());
    }
    for (; pq.size();) {
        double cur_dist;
        uint64_t cur_idx;
        std::tie(cur_dist, cur_idx) = pq.front();
        cur_dist = -cur_dist;
        std::pop_heap(pq.begin(), pq.end());
        pq.pop_back();
        if (cur_idx == to) {
            break;
        }
        if (this->adjacency_list[cur_idx].visited) {
            continue;
        }
        this->adjacency_list[cur_idx].visited = true;
        for (const auto &i : this->adjacency_list[cur_idx].neighbours) {
            double next_dist;
            uint64_t next_idx;
            std::tie(next_idx, next_dist) = i;
            if (cur_dist + next_dist <
                adjacency_list[next_idx].distance) {
                adjacency_list[next_idx].prev = cur_idx;
                adjacency_list[next_idx].distance = cur_dist + next_dist;
                pq.push_back(
                    std::make_tuple(
                        -adjacency_list[next_idx].distance,
                        next_idx
                    )
                );
                std::push_heap(pq.begin(), pq.end());
            }
        }
    }
    if (this->adjacency_list[to].distance == this->infinity) {
        throw NOT_CONNECTED;
    }
    if (verbose) {
        for (uint64_t i = to; i != from; i = this->adjacency_list[i].prev) {
            std::cout << i << "<-\n";
        }
        std::cout << from << '\n';
    }
    return this->adjacency_list[to].distance;
}
