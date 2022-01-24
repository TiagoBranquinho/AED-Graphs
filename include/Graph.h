#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "MinHeap.h"
#include <vector>
#include <list>
#include <iostream>

class Graph {
    struct Edge {
        int dest;   // Destination node stop
        int distGap; // An integer distance interval between node stops
        string line; // line between stops
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist;
        int pred;
        bool visited;
        string lineCon;
        string name; // stop name
        string zone;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

    void dijkstraDistance(int s);
    void dijkstraLines(int s);
    void dijkstraZones(int s);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph();
    Graph(int nodes, bool dir = false);
    vector<Node> &getNodes();

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, const string& line, int weight = 1);

    double dijkstra_distance(int a, int b);
    vector<pair<int,string>> dijkstra_path(int a, int b);
};

#endif
