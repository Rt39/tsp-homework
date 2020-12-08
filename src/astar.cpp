#include "astar.h"
#include <stdexcept>
const std::function<bool(AuxiliaryStar*, AuxiliaryStar*)> Astar::cmp =
    [](AuxiliaryStar* lhs, AuxiliaryStar* rhs) -> bool {
    return lhs->evaluate > rhs->evaluate;
};
Astar::Astar(const Graph& G) : pq(cmp) {
    AuxiliaryStar* t = new AuxiliaryStar(G);
    pq.push(t);
    while (true) {
        AuxiliaryStar* a = pq.top();
        pq.pop();
        if (a->path.size() == G.sizeV()) {
            std::vector<size_t> path = a->path;
            double dist = a->dist;
            delete a;
            while (!pq.empty()) {
                AuxiliaryStar* t = pq.top();
                pq.pop();
                delete t;
            }
            this->path = path;
            this->dist = dist;
            return;
        }
        size_t v = a->path.back();
        for (size_t ind : G.adj(v)) {
            const Edge& e = G.getEdge(ind);
            size_t w = e.other(v);
            if (!a->marked[ w ]) {
                AuxiliaryStar* t2 = new AuxiliaryStar(*a, e);
                pq.push(t2);
            }
        }
        delete a;
    }
    throw std::runtime_error(" impossible to reach ");
}
