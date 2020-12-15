#include "astar.h"
#include <stdexcept>
// comparator needed in priority queue
const std::function<bool(Astar::AuxiliaryStar*, Astar::AuxiliaryStar*)> Astar::cmp =
    [](AuxiliaryStar* lhs, AuxiliaryStar* rhs) -> bool { return lhs->evaluate > rhs->evaluate; };

// nested auxiliary class
Astar::AuxiliaryStar::AuxiliaryStar(const Graph& G)
    : G(G), marked(new bool[G.V]), pq(G.E), dist(0), evaluate(0) {
    for (size_t i = 1; i < G.V; ++i)
        marked[i] = false;
    marked[0] = true;
    path.push_back(0);
    for (size_t i = G.V - 1; i < G.E; ++i)
        pq.insert(i, G.getEdge(i).weight());
}
Astar::AuxiliaryStar::~AuxiliaryStar() { delete[] marked; }
Astar::AuxiliaryStar::AuxiliaryStar(const AuxiliaryStar& orgi, const Edge& e)
    : G(orgi.G), path(orgi.path), marked(new bool[G.V]), pq(orgi.pq), dist(orgi.dist),
      evaluate(orgi.evaluate) {
    std::copy(orgi.marked, orgi.marked + G.V, marked);
    size_t v = path.back(), w = e.other(v);
    if (marked[w]) throw std::invalid_argument("already in path");
    path.push_back(w);
    marked[w] = true;
    dist += e.weight();
    // having searched all the point
    if (path.size() == orgi.G.V) {
        const Edge& e = G.between(w, 0);
        evaluate = dist = dist + e.weight(); // the evaluation and distance is fixed
        return;
    }
    // f(n)=g(n)+h(n)
    // g(n)is the current distance
    // h(n)is the shortest edge able to visit times number of edges left to be visit
    evaluate = dist + (G.V - path.size()) * pq.minElem();
    for (const size_t& e : G.adj(w))
        pq.delElem(e);
}

// doing Astar search
Astar::Astar(const Graph& G) : pq(cmp) {
    AuxiliaryStar* t = new AuxiliaryStar(G);
    pq.push(t);
    while (true) {
        AuxiliaryStar* a = pq.top();
        pq.pop();
        // find a complete route shorter than the minimun evaluation of any other
        if (a->path.size() == G.V) {
            this->path = a->path;
            this->dist = a->dist;
            delete a;
            while (!pq.empty()) {
                AuxiliaryStar* t = pq.top();
                pq.pop();
                delete t;
            }
            return;
        }
        // the current lowest evaluation
        size_t v = a->path.back();
        for (size_t ind : G.adj(v)) {
            const Edge& e = G.getEdge(ind);
            size_t w = e.other(v);
            if (!a->marked[w]) {
                AuxiliaryStar* t2 = new AuxiliaryStar(*a, e);
                pq.push(t2);
            }
        }
        delete a;
    }
    throw std::runtime_error(" impossible to reach ");
}
