#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include <cstddef>
#include <vector>

class Graph {
private:
    const size_t V; // vertex numbers V
    const size_t E; // Edge numbers E=V*(V-1)/2
    Edge* edges; // all edges
    std::vector<size_t>* Adj; // adjcenttable
public:
    Graph(size_t V);
    ~Graph();

    inline size_t sizeV() const;
    inline size_t sizeE() const;
    inline const Edge& getEdge(size_t e) const;
    inline const Edge& between(size_t v, size_t w) const;
    inline const std::vector<size_t>& adj(size_t v) const;
};

inline size_t Graph::sizeV() const { return V; }
inline size_t Graph::sizeE() const { return E; }
inline const Edge& Graph::getEdge(size_t e) const {
    if (e >= E)
        throw std::invalid_argument("index >= edges: V * (V - 1) / 2 =" +
                                    std::to_string(E));
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