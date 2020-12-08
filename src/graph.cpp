#include "graph.h"
#include "graphdefs.h"
#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

Graph::Graph(size_t V) : V(V), E(V * (V - 1) / 2), Adj(new std::vector<size_t>[ V ]) {
    std::allocator<Edge> alloc; // detach memory allocate and construct
    edges = alloc.allocate(E);
    size_t cnt = 0;
    for (size_t i = 0; i < V - 1; ++i)
        for (size_t j = i + 1; j < V; ++j) {
            double dx = coordinate[ i ].first - coordinate[ j ].first,
                   dy = coordinate[ i ].second - coordinate[ j ].second;
            // Euclidean distance between two vertexs
            alloc.construct(edges + cnt, cnt, i, j, std::sqrt(dx * dx + dy * dy));
            cnt++;
        }
    // construct adjcent table
    for (size_t i = 0; i < E; ++i) {
        size_t v = edges[ i ].either(), w = edges[ i ].other(v);
        Adj[ v ].push_back(i);
        Adj[ w ].push_back(i);
    }
}
Graph::~Graph() {
    delete[] Adj;
    std::allocator<Edge> alloc;
    for (size_t i = 0; i < E; ++i)
        alloc.destroy(edges + i);
    alloc.deallocate(edges, E);
}
