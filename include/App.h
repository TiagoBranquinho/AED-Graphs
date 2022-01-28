#ifndef GRAPHS_AED_APP_H
#define GRAPHS_AED_APP_H

#include "Data.h"
#include "GraphGN.h"
#include "structs.h"
#include "GraphLines.h"

#include <fstream>

class App {
public:
    int maxWalkDist = 0;
    Data data;
    GraphGN dayGraph;
    GraphGN nightGraph;
    GraphLines dayGraphLines;
    GraphLines nightGraphLines;

public:
    App();
    void loadData();
    Data getData();
    GraphGN getGraph();
    int getMaxWalkDist();
    void setMaxWalkDist(int dist);
    void resetGraphs();

    void createGraphs();
    void createLinePath(GraphGN &graph, std::string line, std::vector<std::string> path);
    void createLinePath(GraphLines &graph, map<int, int> &connector, std::string line, std::vector<std::string> path);
    void createWalkPaths(int maxDist);
    void createWalkPaths();
    void connectLinesWalks(GraphLines &graph);

    void addWalkPathsToNode(int node, int direction);
    int addLocalNode(pair<double, double> local, string name, int direction);
    void removeLocalNode(int node);

    void viewPath(vector<pair<int, string>> path, const string& time);
    void bestPathSTOPS(int src, int dest);
    void bestPathDIST(int src, int dest);
    void bestPathLINES(int src, int dest);
    void bestPathZONES(GraphLines graph, int src, int dest);

    int distance(int src, int dest);
    static int haversine(double lat1, double lon1, double lat2, double lon2);
};

#endif //GRAPHS_AED_APP_H
