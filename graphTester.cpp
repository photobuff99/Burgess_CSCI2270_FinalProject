// This file is used to test the graph class
#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
    Graph G;
    G.addVertex(1234,223, false);
    G.addVertex(1234,23123, false);
    G.addVertex(154,2123, true);
    cout << G.getXpos(0) << " " << G.getXpos(0) << endl;
    cout << G.getXpos(1) << " " << G.getXpos(1) << endl;
    cout << G.getXpos(2) << " " << G.getXpos(100) << endl;
    return 0;
}
