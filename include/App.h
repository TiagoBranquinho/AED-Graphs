#ifndef GRAPHS_AED_APP_H
#define GRAPHS_AED_APP_H

#include "Data.h"
#include "Graph.h"

class App {
public:
    Data data;
    Graph graph;

public:
    App();
    void loadData();
    void createGraph();
    void createLinePath(std::string line, std::vector<std::string> path);
    void createWalkPaths(int maxDist);

    void viewPath(vector<pair<int,string>> path);
    int distance(int src, int dest);
    static int haversine(double lat1, double lon1, double lat2, double lon2);
};


#endif //GRAPHS_AED_APP_H
