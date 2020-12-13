#include "astar.h"
#include "genetic.h"
#include <ctime>
#include <iostream>
#include <stdlib.h>

using namespace std;
int main() {
    Graph g(11);
    time_t t1 = clock();
    Astar asw(g);
    time_t t2 = clock();
    cout << t2 - t1 << "\n";
    for (auto i : asw.shortestPath())
        cout << i << " ";
    cout << "\n";
    cout << asw.shortestDistance() << "\n";
    Genetic gasw(g);
    for (auto i : gasw.runPath())
        cout << i << " ";
    cout << "\n";
    cout << gasw.runDist();
}