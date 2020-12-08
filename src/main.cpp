#include "astar.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
    Graph g(4);
    Astar asw(g);
    for (auto i : asw.shortestPath())
        cout << i << " ";
    cout << "\n";
    cout << asw.shortestDistance();
}