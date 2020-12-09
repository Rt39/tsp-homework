#ifndef EDGE_H
#define EDGE_H

#include <cstddef>
#include <stdexcept>

class Edge {
private:
    const size_t no; // edge number
    const size_t v; // one vertex
    const size_t w; // another vertex
    const double wei; // weight of edge
public:
    Edge(size_t No, size_t v, size_t w, double weight);

    double weight() const;
    size_t No() const;
    size_t either() const;
    size_t other(size_t vertex) const;
};
inline double Edge::weight() const { return this->wei; }
inline size_t Edge::No() const { return no; }
inline size_t Edge::either() const { return v; }
inline size_t Edge::other(size_t vertex) const {
    if (vertex == v)
        return w;
    else if (vertex == w)
        return v;
    else
        throw std::invalid_argument("Inconsistent edge");
}

#endif