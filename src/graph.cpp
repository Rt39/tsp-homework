#include "graph.h"
#include "graphdefs.h"
#include <cmath>
#include <memory>
#include <random>
#include <stdexcept>
#include <stdio.h>
#include <string>

using namespace graphdefs;

Graph::Graph(size_t V, unsigned SEED)
    : V(V), E(V * (V - 1) / 2), SEED(SEED), Adj(new std::vector<size_t>[ V ]) {
    generateCoordinate(-200, 200, SEED);
    constructGraph();
}
Graph::Graph(size_t V, double min, double max, unsigned SEED)
    : V(V), E(V * (V - 1) / 2), SEED(SEED), Adj(new std::vector<size_t>[ V ]) {
    generateCoordinate(min, max, SEED);
    constructGraph();
}
Graph::Graph(size_t V, const char* file)
    : V(V), E(V * (V - 1) / 2), SEED(-1), Adj(new std::vector<size_t>[ V ]) {
    FILE* coordinateFile = fopen(file, "r");
    if (coordinateFile == nullptr) throw std::invalid_argument("Unable to open file");
    for (size_t i = 0; i < V; ++i)
        if (fscanf(coordinateFile, "%lf%lf", &coordinate[ i ].first, &coordinate[ i ].second) != 2)
            throw std::runtime_error(
                "Either you input the wrong vertex number or the format of the file is not right");
    fclose(coordinateFile);
    constructGraph();
}
Graph::~Graph() {
    delete[] Adj;
    std::allocator<Edge> alloc;
    for (size_t i = 0; i < E; ++i)
        alloc.destroy(edges + i);
    alloc.deallocate(edges, E);
}

void Graph::generateCoordinate(double min, double max, unsigned SEED) {
    std::default_random_engine randomEngine(SEED);
    std::uniform_real_distribution<double> ur(min, max);
    FILE* generateFile = fopen("generate.txt", "w+");
    if (generateFile == nullptr)
        throw std::runtime_error("Unable to write or generate \"genrate.txt\"");
    for (size_t i = 0; i < V; ++i) {
        double x = ur(randomEngine), y = ur(randomEngine);
        coordinate[ i ] = std::make_pair(x, y);
        fprintf(generateFile, "%lf %lf\n", x, y);
    }
    fclose(generateFile);
}
void Graph::constructGraph() {
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