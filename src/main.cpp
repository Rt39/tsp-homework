#include "astar.h"
#include "genetic.h"
#include <ctime>
#include <iostream>
#include <stdlib.h>

using namespace std;
int main() {
    Graph g(10, 0u);
    time_t t1 = clock();
    Astar asw(g);
    time_t t2 = clock();
    cout << t2 - t1 << "\n";
    for (auto i : asw.shortestPath())
        cout << i << " ";
    cout << "\n";
    cout << asw.shortestDistance() << "\n";
    time_t t3 = clock();
    Genetic gasw(g, 20, 0.95, 0.01, 20000);
    time_t t4 = clock();
    cout << t4 - t3 << "\n";
    for (auto i : gasw.runPath())
        cout << i << " ";
    cout << "\n";
    cout << gasw.runDist();
}