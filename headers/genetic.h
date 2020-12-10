#ifndef GENETIC_H
#define GENETIC_H

#include "graph.h"
#include <utility>
#include <vector>

class Genetic {
private:
    struct population {
        const Graph& G;
        const size_t V;
        size_t* arrangement;
        double dist;
        double eval;

        population(const Graph& G);
        population(const population&) = delete;
        population& operator=(const population&) = delete;
        ~population();

        void updateDist();
        void mutate();
    };

private:
    const Graph& G;
    const size_t V;
    const size_t POPULATION_NUM;
    const double CROSS_RATE;
    const double MUTATION_RATE;
    const size_t ITERATION_NUM;
    population* p;
    std::vector<size_t> path;
    double dist;

    std::pair<size_t, size_t> choose();
    void cross();

public:
    Genetic(const Graph& G, size_t population_num = 20, double cross_rate = 0.9,
            double mutation_rate = 0.01, size_t iteration_num = 50);
    ~Genetic();

    inline std::vector<size_t> runPath() const;
    inline double runDist() const;
};

inline std::vector<size_t> Genetic::runPath() const { return path; }
inline double Genetic::runDist() const { return dist; }

#endif