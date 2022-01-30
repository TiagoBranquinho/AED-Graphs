#ifndef GRAPHS_AED_GRAPHLINES_H
#define GRAPHS_AED_GRAPHLINES_H

#include "Graph.h"

#include <string>
#include <vector>

class GraphLines : public Graph{

    /**
     * Dijkstra algorithm that calculates the minimum lines changes to every node in the nodes vector starting from s node
     * @param s integer index of the source node in nodes vector
     */
    void dijkstraLines(std::vector<int> s);

public:

    /**
     * Method that uses the dijkstraLines algorithm and calculates the minimum number of line changes starting from node a to node b
     * @param a integer index of the source node in nodes vector
     * @param b integer index of the destination node in nodes vector
     * @return integer number of lines changes
     */
    int dijkstraDistanceLN(std::vector<int> a, std::vector<int> b);
    /**
     * Method that uses the dijkstraLines algorithm and calculates the path with minimum number of line changes starting from node a to node b
     * @param a integer index of the source node in nodes vector
     * @param b integer index of the destination node in nodes vector
     * @return vector with all stops in the path represented by the pairs
     */
    std::vector<std::pair<int,std::string>> dijkstraPathLN(std::vector<int> a, std::vector<int> b);
    /**
     * Gets the node with the minimum line changes of a given dest vector of node indexes
     * @param dest vector with the index of the nodes in the nodes vector
     * @return integer index of the node with less line changes
     */
    int minDest(std::vector<int> dest);
};


#endif //GRAPHS_AED_GRAPHLINES_H
