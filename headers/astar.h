#ifndef ASTAR_H
#define ASTAR_H

#include "graph.h"
#include "indexminpq.h"
#include <functional>
#include <queue>

class Astar {
private:
    // an auxiliary class contains everything needed in Astar Algorithm
    struct AuxiliaryStar {
        const Graph& G;
        std::vector<size_t> path; // conserve the path having been searched
        bool* marked; // mark the path that already visited
        IndexMinPQ pq; // conserve all the pathes which are possible to visit
        double dist; // distance that are already visited
        double evaluate; // f(x) minimal evaluation of the total distance

        AuxiliaryStar(const Graph& G);
        ~AuxiliaryStar();
        AuxiliaryStar(const AuxiliaryStar&) = delete;
        AuxiliaryStar& operator=(const AuxiliaryStar&) = delete;
        AuxiliaryStar(const AuxiliaryStar& orgi, const Edge& e);
    };

private:
    static const std::function<bool(AuxiliaryStar*, AuxiliaryStar*)> cmp;
    std::priority_queue<AuxiliaryStar*, std::vector<AuxiliaryStar*>, decltype(cmp)> pq;
    std::vector<size_t> path;
    double dist;

public:
    Astar(const Graph& G);

    std::vector<size_t> shortestPath() const;
    double shortestDistance() const;
};
inline std::vector<size_t> Astar::shortestPath() const { return path; }
inline double Astar::shortestDistance() const { return dist; }
#endif