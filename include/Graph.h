#ifndef GRAPHS_AED_GRAPH_H
#define GRAPHS_AED_GRAPH_H

#include "structs.h"

#include <vector>
#include <list>
#include <climits>

#define INF (INT_MAX/2)

class Graph {

protected:
    int n=0;
    bool hasDir=true;
    std::vector<Node> nodes={{}};

public:
    Graph(bool hasDir = true);

    std::vector<Node> &getNodes();
    int addNode(const Node& node);
    void removeNode(int node);
    void addEdge(int src, int dest, const std::string& line, int weight);
    std::list<std::pair<int,std::string>> buildPath(int a, int b);
};


#endif //GRAPHS_AED_GRAPH_H
