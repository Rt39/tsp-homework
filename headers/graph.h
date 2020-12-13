#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include <cstddef>
#include <ctime>
#include <vector>


class Graph {
public:
    const size_t V; // vertex numbers V
    const size_t E; // edge numbers E=V*(V-1)/2
    const long SEED; // seed of the random generator. If it is -1, you are reading edges from a file

private:
    Edge* edges; // all edges
    std::vector<size_t>* Adj; // adjcenttable

    void generateCoordinate(double min, double max, unsigned seed);
    void constructGraph();

public:
    Graph(size_t V, unsigned SEED = time(nullptr));
    Graph(size_t V, double min, double max, unsigned SEED = time(nullptr));
    Graph(size_t V, const char* file);
    ~Graph();

    inline const Edge& getEdge(size_t e) const;
    inline const Edge& between(size_t v, size_t w) const;
    inline const std::vector<size_t>& adj(size_t v) const;
};

inline const Edge& Graph::getEdge(size_t e) const {
    if (e >= E)
        throw std::invalid_argument("index >= edges: V * (V - 1) / 2 =" + std::to_string(E));
    return edges[ e ];
}
inline const Edge& Graph::between(size_t v, size_t w) const {
    if (v == w) throw std::invalid_argument("no edge between oneself");
    size_t a = std::min(v, w), b = std::max(v, w);
    return getEdge(Adj[ a ][ b - 1 ]);
}
inline const std::vector<size_t>& Graph::adj(size_t v) const {
    if (v >= V) throw std::invalid_argument("index >= vetexs: " + std::to_string(V));
    return Adj[ v ];
}

#endif