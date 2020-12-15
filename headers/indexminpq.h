#ifndef INDEXMINPQ_H
#define INDEXMINPQ_H

#include <cstddef>
#include <stdexcept>
#include <utility>

class IndexMinPQ {
private:
    const size_t maxN;
    size_t n;
    size_t *pq, *qp;
    double* elem;

    inline void exch(size_t i, size_t j);
    void swim(size_t k);
    void sink(size_t k);
    inline void validateIndex(size_t i) const;

public:
    IndexMinPQ(size_t maxN);
    IndexMinPQ(const IndexMinPQ& orgi);
    IndexMinPQ& operator=(const IndexMinPQ&) = delete;
    ~IndexMinPQ();

    void insert(size_t i, double val);
    void delElem(size_t i);
    bool contains(size_t i) const;
    size_t size() const;
    double minElem() const;
};
inline void IndexMinPQ::exch(size_t i, size_t j) {
    std::swap(pq[i], pq[j]);
    std::swap(qp[pq[i]], qp[pq[j]]);
}
inline void IndexMinPQ::validateIndex(size_t i) const {
    if (i >= maxN) throw std::invalid_argument("index >= capacity: " + std::to_string(i));
}
inline bool IndexMinPQ::contains(size_t i) const {
    validateIndex(i);
    return qp[i] != 0;
}
inline size_t IndexMinPQ::size() const { return n; }
inline double IndexMinPQ::minElem() const {
    if (n == 0) throw std::underflow_error("priority queue is empty");
    return elem[pq[1]];
}

#endif // INDEXMINPQ