#include "indexminpq.h"
#include <algorithm>
#include <stdexcept>
#include <string>

// constructor and destructor
IndexMinPQ::IndexMinPQ(size_t maxN)
    : maxN(maxN), n(0), pq(new size_t[ maxN + 1 ]), qp(new size_t[ maxN + 1 ]),
      elem(new double[ maxN + 1 ]) {
    for (size_t i = 0; i <= maxN; ++i)
        qp[ i ] = 0;
}
IndexMinPQ::IndexMinPQ(const IndexMinPQ& orig)
    : maxN(orig.maxN), n(orig.n), pq(new size_t[ maxN + 1 ]), qp(new size_t[ maxN + 1 ]),
      elem(new double[ maxN + 1 ]) {
    std::copy(orig.pq, orig.pq + n + 1, pq);
    std::copy(orig.qp, orig.qp + maxN + 1, qp);
    std::copy(orig.elem, orig.elem + maxN + 1, elem);
}
IndexMinPQ::~IndexMinPQ() {
    delete[] pq;
    delete[] qp;
    delete[] elem;
}

// private functions

void IndexMinPQ::swim(size_t k) {
    while (k > 1 && elem[ pq[ k / 2 ] ] > elem[ pq[ k ] ]) {
        exch(k, k / 2);
        k = k / 2;
    }
}
void IndexMinPQ::sink(size_t k) {
    while (2 * k <= n) {
        size_t j = 2 * k;
        if (j < n && elem[ pq[ j ] ] > elem[ pq[ j + 1 ] ]) ++j;
        if (elem[ pq[ k ] ] <= elem[ pq[ j ] ]) break;
        exch(k, j);
        k = j;
    }
}

// public functions
void IndexMinPQ::insert(size_t i, double val) {
    validateIndex(i);
    if (n == maxN) throw std::overflow_error("priority queue is full");
    if (contains(i))
        throw std::invalid_argument("index is already in the priority queue");
    ++n;
    qp[ i ] = n;
    elem[ i ] = val;
    pq[ n ] = i;
    swim(n);
}
void IndexMinPQ::delElem(size_t i) {
    validateIndex(i);
    if (!contains(i)) {
        // throw std::invalid_argument("index is not in the priority queue");
        return;
    }
    size_t index = qp[ i ];
    exch(index, n--);
    swim(index);
    sink(index);
    elem[ i ] = 0.0;
    qp[ i ] = 0;
}
