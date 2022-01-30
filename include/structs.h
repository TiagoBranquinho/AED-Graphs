#ifndef GRAPHS_AED_STRUCTS_H
#define GRAPHS_AED_STRUCTS_H

#include <string>
#include <list>

struct Edge {
    /** Destination node stop */
    int dest;
    /** An integer distance interval between node stops */
    int distGap;
    /** line between stops */
    std::string line;
};

struct Node {
    /** The list of outgoing edges (to adjacent nodes) */
    std::list<Edge> adj;
    /** distance variable used in dijkstra algorithms for minimum distance calculations */
    int dist;
    /** used in bfs algorithms for minimum stop changes calculations */
    int stopChanges;
    /** used in dijkstra algorithms for minimum line changes calculations */
    int lineChanges;
    /** used in dijkstra algorithms for minimum zone changes calculations */
    int zoneChanges;
    /** used to save the predecessor node */
    int pred;
    bool visited;
    /** used to save the line connection used to go to this node */
    std::string lineCon;
    /** line that the node belongs in the GraphLines graph */
    std::string line;
    /** stop name */
    std::string name;
    /** stop zone*/
    std::string zone;
};

struct Stop{
    std::string code;
    std::string name;
    std::string zone;
    double latitude;
    double longitude;
};

#endif //GRAPHS_AED_STRUCTS_H
