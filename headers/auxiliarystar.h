#ifndef AUXILIARYSTAR_H
#define AUXILIARYSTAR_H

#include "edge.h"
#include "graph.h"
#include "indexminpq.h"
#include <vector>

// a class contains all information for Astar algorithm to carry
class AuxiliaryStar {
    friend class Astar;

private:
    const Graph& G;
    std::vector<size_t> path;
    bool* marked;
    IndexMinPQ pq;
    double dist;
    double evaluate;

public:
    AuxiliaryStar(const Graph& G);
    ~AuxiliaryStar();
    AuxiliaryStar(const AuxiliaryStar&) = delete;
    AuxiliaryStar& operator=(const AuxiliaryStar&) = delete;
    AuxiliaryStar(const AuxiliaryStar& orgi, const Edge& e);
};

#endif