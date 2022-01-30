#ifndef GRAPHS_AED_STRUCTS_H
#define GRAPHS_AED_STRUCTS_H

#include <string>
#include <list>

struct Edge {
    int dest;   /** Destination node stop */
    int distGap; /** An integer distance interval between node stops */
    std::string line; /** line between stops */
};

struct Node {
    std::list<Edge> adj; /** The list of outgoing edges (to adjacent nodes) */
    int dist; /** distance variable used in dijkstra algorithms for minimum distance calculations */
    int stopChanges; /** used in bfs algorithms for minimum stop changes calculations */
    int lineChanges; /** used in dijkstra algorithms for minimum line changes calculations */
    int zoneChanges; /** used in dijkstra algorithms for minimum zone changes calculations */
    int pred; /** used to save the predecessor node */
    bool visited;
    std::string lineCon; /** used to save the line connection used to go to this node */
    std::string line; /** line that the node belongs in the GraphLines graph */
    std::string name; /** stop name */
    std::string zone; /** stop zone*/
};

struct Stop{
    std::string code;
    std::string name;
    std::string zone;
    double latitude;
    double longitude;
};

#endif //GRAPHS_AED_STRUCTS_H
