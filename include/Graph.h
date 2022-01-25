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
        int stopChanges;
        int lineChanges;
        int zoneChanges;
        int pred;
        bool visited;
        string lineCon;
        string name; // stop name
        string zone;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented

    void bfsStops(int s);
    void dijkstraDist(int s);
    void dijkstraLines(int s);
    void dijkstraZones(int s);

public:

    // Constructor: nr nodes and direction (default: undirected)
    Graph();
    Graph(int nodes, bool dir = false);
    vector<Node> &getNodes();
    void addNodeN();
    void removeNodeN();

    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, const string& line, int weight = 1);
    list<pair<int,string>> buildPath(int a, int b);

    int bfsDistanceST(int a, int b);
    vector<pair<int,string>> bfsPathST(int a, int b);
    int dijkstraDistanceDS(int a, int b);
    vector<pair<int,string>> dijkstraPathDS(int a, int b);
    int dijkstraDistanceLN(int a, int b);
    vector<pair<int,string>> dijkstraPathLN(int a, int b);
    int dijkstraDistanceZN(int a, int b);
    vector<pair<int,string>> dijkstraPathZN(int a, int b);
};

#endif
