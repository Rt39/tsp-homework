#include "auxiliarystar.h"
#include <stdexcept>

AuxiliaryStar::AuxiliaryStar(const Graph& G)
    : G(G), marked(new bool[ G.sizeV() ]), pq(G.sizeE()), dist(0), evaluate(0) {
    for (size_t i = 1; i < G.sizeV(); ++i)
        marked[ i ] = false;
    marked[ 0 ] = true;
    path.push_back(0);
    for (size_t i = G.sizeV() - 1; i < G.sizeE(); ++i)
        pq.insert(i, G.getEdge(i).weight());
}
AuxiliaryStar::~AuxiliaryStar() { delete[] marked; }
AuxiliaryStar::AuxiliaryStar(const AuxiliaryStar& orgi, const Edge& e)
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