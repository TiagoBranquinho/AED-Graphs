#ifndef GRAPHS_AED_STRUCTS_H
#define GRAPHS_AED_STRUCTS_H

#include <string>
#include <list>

struct Edge {
    int dest;   // Destination node stop
    int distGap; // An integer distance interval between node stops
    std::string line; // line between stops
};

struct Node {
    std::list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    int dist;
    int stopChanges;
    int lineChanges;
    int zoneChanges;
    int pred;
    bool visited;
    std::string lineCon;
    std::string line; // line that the node belongs in the GraphLines
    std::string name; // stop name
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
