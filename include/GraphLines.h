#ifndef GRAPHS_AED_GRAPHLINES_H
#define GRAPHS_AED_GRAPHLINES_H

#include "Graph.h"

#include <string>
#include <vector>

class GraphLines : public Graph{
    void dijkstraLines(int s);

public:

    int dijkstraDistanceLN(int a, int b);
    std::vector<std::pair<int,std::string>> dijkstraPathLN(int a, int b);
};


#endif //GRAPHS_AED_GRAPHLINES_H
