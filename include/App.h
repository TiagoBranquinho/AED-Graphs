#ifndef GRAPHS_AED_APP_H
#define GRAPHS_AED_APP_H

#include "Data.h"
#include "GraphGN.h"
#include "structs.h"
#include "GraphLines.h"

#include <fstream>

class App {
public:
    enum MODE {DAY, NIGHT};
    map<MODE, GraphGN> graphGN;
    map<MODE, GraphLines> graphLN;
    MODE CURRENT_MODE = DAY;

private:
    int maxWalkDist = 0;
    Data data;
    GraphGN dayGraph;
    GraphGN nightGraph;
    GraphLines dayGraphLines;
    GraphLines nightGraphLines;

public:
    App();
    void loadData();
    Data &getData();
    GraphGN &getGraphGN();
    GraphLines &getGraphLN();
    int getMaxWalkDist();
    void setMaxWalkDist(int dist);
    MODE currentMode() const;
    void setCurrentMode(MODE mode);
    std::map<int,int> &getConnector();
    std::map<int,std::vector<int>> &getInverter();
    void resetGraphs();

    void createGraphs();
    void createLinePath(GraphGN &graph, std::string line, std::vector<std::string> path);
    void createLinePath(GraphLines &graph, map<int, int> &connector, map<int, vector<int>> &inverter, std::string line, std::vector<std::string> path);
    void createWalkPaths();

    void addWalkPathsToNode(int node, int direction);
    int addLocalNode(pair<double, double> local, string name, int direction);
    void removeLocalNode(int node);

    void viewPath(vector<pair<int, string>> path, bool graphLN);

    int distance(int src, int dest);
    static int haversine(double lat1, double lon1, double lat2, double lon2);
};

#endif //GRAPHS_AED_APP_H
