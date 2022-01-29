#ifndef GRAPHS_AED_GRAPHLINES_H
#define GRAPHS_AED_GRAPHLINES_H

#include "Graph.h"

#include <string>
#include <vector>

class GraphLines : public Graph{
    void dijkstraLines(std::vector<int> s);

public:

    int dijkstraDistanceLN(std::vector<int> a, std::vector<int> b);
    std::vector<std::pair<int,std::string>> dijkstraPathLN(std::vector<int> a, std::vector<int> b);
    int minDest(std::vector<int> dest);
};


#endif //GRAPHS_AED_GRAPHLINES_H
