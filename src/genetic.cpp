#include "genetic.h"
#include <algorithm>
#include <random>
#include <unordered_set>

std::default_random_engine random_engine;

Genetic::population::population(const Graph& G)
    : G(G), V(G.sizeV()), arrangement(new size_t[ V ]) {
    for (size_t i = 0; i < V; ++i)
        arrangement[ i ] = i;
    std::shuffle(arrangement, arrangement + V, random_engine);
    updateDist();
}
Genetic::population::~population() { delete[] arrangement; }

void Genetic::population::updateDist() {
    dist = 0;
    for (size_t i = 0; i < V; ++i)
        dist += G.between(arrangement[ i ], arrangement[ (i + 1) % V ]).weight();
    eval = 1.0 / (1.0 + dist);
}
void Genetic::population::mutate() {
    std::uniform_int_distribution<size_t> u(0, V - 1);
    size_t a = u(random_engine), b = u(random_engine);
    std::swap(arrangement[ a ], arrangement[ b ]);
    updateDist();
}

std::pair<size_t, size_t> Genetic::choose() {
    double evalsum[ V ];
    double sum = 0;
    for (size_t i = 0; i < V; ++i)
        evalsum[ i ] = (sum += p[ i ].eval);
    std::uniform_real_distribution<double> u(0.0, sum);
    double a = u(random_engine), b = u(random_engine);
    double *l = std::lower_bound(evalsum, evalsum + V, a),
           *r = std::lower_bound(evalsum, evalsum + V, b);
    return {l - evalsum, r - evalsum};
}
void Genetic::cross() {
    auto [ a, b ] = choose();
    std::uniform_int_distribution<size_t> u(0, V);
    size_t r1 = u(random_engine), r2 = u(random_engine);
    size_t lft = std::min(r1, r2), rht = std::max(r1, r2);
    size_t *fir = p[ a ].arrangement, *sec = p[ b ].arrangement;
    size_t fir_cop[ V ];
    std::copy(fir, fir + V, fir_cop);
    std::unordered_set<size_t> fir_gene(fir + lft, fir + rht),
        sec_gene(sec + lft, sec + rht);
    for (size_t i = 0, j = 0; i < V && j < V; ++j) {
        if (i == lft) i = rht;
        if (!fir_gene.count(sec[ j ])) {
            fir[ i ] = sec[ j ];
            ++i;
        }
    }
    for (size_t i = 0, j = 0; i < V && j < V; ++j) {
        if (i == lft) i = rht;
        if (!sec_gene.count(fir_cop[ j ])) {
            sec[ i ] = fir_cop[ j ];
            ++i;
        }
    }
    p[ a ].updateDist();
    p[ b ].updateDist();
}

Genetic::Genetic(const Graph& G, size_t population_num, double cross_rate,
                 double mutation_rate, size_t iteration_num)
    : G(G), V(G.sizeV()), POPULATION_NUM(population_num), CROSS_RATE(cross_rate),
      MUTATION_RATE(mutation_rate), ITERATION_NUM(iteration_num) {
    std::allocator<population> alloc;
    p = alloc.allocate(POPULATION_NUM);
    for (size_t i = 0; i < POPULATION_NUM; ++i)
        alloc.construct(p + i, G);
    for (size_t i = 0; i < ITERATION_NUM; ++i) {
        std::uniform_real_distribution<double> ur(0.0, 1.0);
        if (ur(random_engine) < CROSS_RATE) cross();
        if (ur(random_engine) < MUTATION_RATE) {
            std::uniform_int_distribution<size_t> ui(0, V - 1);
            p[ ui(random_engine) ].mutate();
        }
    }
    size_t best = 0;
    for (size_t i = 0; i < V; ++i)
        if (p[ i ].dist < p[ best ].dist) best = i;
    path = std::vector<size_t>(p[ best ].arrangement, p[ best ].arrangement + V);
    dist = p[ best ].dist;
}
Genetic::~Genetic() {
    std::allocator<population> alloc;
    for (size_t i = 0; i < POPULATION_NUM; ++i)
        alloc.destroy(p + i);
    alloc.deallocate(p, POPULATION_NUM);
}