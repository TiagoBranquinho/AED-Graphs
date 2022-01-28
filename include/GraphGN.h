#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "MinHeap.h"
#include "structs.h"
#include "Graph.h"

#include <vector>
#include <list>
#include <iostream>

class GraphGN : public Graph{

    void bfsStops(int s);
    void dijkstraDist(int s);
    void dijkstraZones(int s);

public:

    int bfsDistanceST(int a, int b);
    vector<pair<int,string>> bfsPathST(int a, int b);
    int dijkstraDistanceDS(int a, int b);
    vector<pair<int,string>> dijkstraPathDS(int a, int b);
    int dijkstraDistanceZN(int a, int b);
    vector<pair<int,string>> dijkstraPathZN(int a, int b);
};

#endif
