#include "astar.h"
#include <stdexcept>
const std::function<bool(Astar::AuxiliaryStar*, Astar::AuxiliaryStar*)> Astar::cmp =
    [](AuxiliaryStar* lhs, AuxiliaryStar* rhs) -> bool {
    return lhs->evaluate > rhs->evaluate;
};

// nested auxiliary class
Astar::AuxiliaryStar::AuxiliaryStar(const Graph& G)
    : G(G), marked(new bool[ G.sizeV() ]), pq(G.sizeE()), dist(0), evaluate(0) {
    for (size_t i = 1; i < G.sizeV(); ++i)
        marked[ i ] = false;
    marked[ 0 ] = true;
    path.push_back(0);
    for (size_t i = G.sizeV() - 1; i < G.sizeE(); ++i)
        pq.insert(i, G.getEdge(i).weight());
}
Astar::AuxiliaryStar::~AuxiliaryStar() { delete[] marked; }
Astar::AuxiliaryStar::AuxiliaryStar(const AuxiliaryStar& orgi, const Edge& e)
    : G(orgi.G), path(orgi.path), marked(new bool[ G.sizeV() ]), pq(orgi.pq),
      dist(orgi.dist), evaluate(orgi.evaluate) {
    std::copy(orgi.marked, orgi.marked + G.sizeV(), marked);
    size_t v = path.back(), w = e.other(v);
    if (marked[ w ]) throw std::invalid_argument("already in path");
    path.push_back(w);
    marked[ w ] = true;
    dist += e.weight();
    if (path.size() == orgi.G.sizeV()) {
        const Edge& e = G.between(w, 0);
        evaluate = dist = dist + e.weight();
        return;
    }
    evaluate = dist + (G.sizeV() - path.size() + 1) * pq.minElem();
    for (const size_t& e : G.adj(w))
        pq.delElem(e);
}

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
