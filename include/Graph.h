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
    /**
     * Graph class default constructor
     * @param hasDir true if graph is directed or false otherwise
     */
    Graph(bool hasDir = true);

    /**
     * Gets a reference to get nodes vector of the graph
     * @return node vector passed by reference
     */
    std::vector<Node> &getNodes();
    /**
     * Adds a node to the graph
     * @param node Node struct information
     * @return index of the position where the node was added in the nodes vector
     */
    int addNode(const Node& node);
    /**
     * Removes the node correspondent to the integer node identifier passed in the argument
     * @param node integer node identifier in the nodes vector
     */
    void removeNode(int node);
    /**
     * Adds an edge to the src node
     * @param src integer source node index in the nodes vector
     * @param dest integer destination node index in the nodes vector
     * @param line line string of the connections between the nodes
     * @param weight weight of the edge
     */
    void addEdge(int src, int dest, const std::string& line, int weight);
    /**
     * Creates a list of pairs representing the stops and lines that connects those stops
     * @param a integer index of the source node in the nodes vector
     * @param b integer index of the destination node in the nodes vector
     * @return list of pair in the first element being the stop index and the second the line the connects to the next stop in the list
     */
    std::list<std::pair<int,std::string>> buildPath(int a, int b);
};


#endif //GRAPHS_AED_GRAPH_H
