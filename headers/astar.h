#ifndef ASTAR_H
#define ASTAR_H

#include "auxiliarystar.h"
#include <functional>
#include <queue>

class Astar {
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