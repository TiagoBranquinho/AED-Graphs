#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "MinHeap.h"
#include "structs.h"
#include "Graph.h"

#include <vector>
#include <list>
#include <iostream>

class GraphGN : public Graph{

    /**
     * BFS algorithm that calculates the minimum stops changes to every node in the nodes vector starting from s node
     * @param s integer index of the source node in nodes vector
     */
    void bfsStops(int s);
    /**
     * Dijkstra algorithm that calculates the minimum distance to every node in the nodes vector starting from s node
     * @param s integer index of the source node in nodes vector
     */
    void dijkstraDist(int s);
    /**
     * Dijkstra algorithm that calculates the minimum zones changes to every node in the nodes vector starting from s node
     * @param s integer index of the source node in nodes vector
     */
    void dijkstraZones(int s);

public:

    /**
     * Method that uses the bfsStops algorithm and calculates the minimum number of stops starting from node a to node b
     * @param a integer index of the source node in nodes vector
     * @param b integer index of the destination node in nodes vector
     * @return integer number of stops changes
     */
    int bfsDistanceST(int a, int b);
    /**
     * Method that uses the bfsStops algorithm and calculates the path with minimum number of stops starting from node a to node b
     * @param a integer index of the source node in nodes vector
     * @param b integer index of the destination node in nodes vector
     * @return vector with all stops in the path represented by the pairs
     */
    vector<pair<int,string>> bfsPathST(int a, int b);
    /**
     * Method that uses the dijkstraDist algorithm and calculates the minimum distance in meters starting from node a to node b
     * @param a integer index of the source node in nodes vector
     * @param b integer index of the destination node in nodes vector
     * @return integer distance in meters
     */
    int dijkstraDistanceDS(int a, int b);
    /**
     * Method that uses the dijkstraDist algorithm and calculates the minimum distance path starting from node a to node b
     * @param a integer index of the source node in nodes vector
     * @param b integer index of the destination node in nodes vector
     * @return vector with all stops in the path represented by the pairs
     */
    vector<pair<int,string>> dijkstraPathDS(int a, int b);
    /**
     * Method that uses the dijkstraZones algorithm and calculates the minimum number of zones changes starting from node a to node b
     * @param a integer index of the source node in nodes vector
     * @param b integer index of the destination node in nodes vector
     * @return integer numbers of zone changes
     */
    int dijkstraDistanceZN(int a, int b);
    /**
     * Method that uses the dijkstraZones algorithm and calculates the path with minimum number of zones changes starting from node a to node b
     * @param a integer index of the source node in nodes vector
     * @param b integer index of the destination node in nodes vector
     * @return vector with all stops in the path represented by the pairs
     */
    vector<pair<int,string>> dijkstraPathZN(int a, int b);
};

#endif
