#include "../include/App.h"

#include <iostream>
#include <cmath>

App::App() {
    loadData();
}

void App::loadData() {
    data.readLines();
    data.readStops();
}

void App::createGraph() {
    int nodes = (int)data.nodes.size();
    graph = Graph(nodes, true);
    for (const auto& line : data.lines) {
        vector<string> path0 = data.readLinePath(line.first,"0");
        vector<string> path1 = data.readLinePath(line.first,"1");
        createLinePath(line.first, path0);
        createLinePath(line.first, path1);
    }
    for (int i = 1; i < graph.getNodes().size(); i++){
        graph.getNodes()[i].name = data.getStop(i);
    }
}

void App::createLinePath(string line, vector<string> path) {
    if (path.empty()) return;
    for (int i = 0; i < path.size() - 1; i++) {
        int src = data.getNode(path[i]);
        int dest = data.getNode(path[i+1]);
        graph.addEdge(src, dest, line, distance(src, dest));
    }
}

void App::createWalkPaths(int maxDist) {
    size_t size = data.stopsVector.size();
    for (int i = 0; i < size; i++){
        for (int j = i+1; j < size - 1; j++){
            int dist = distance(i,j);
            if (dist <= maxDist){
                graph.addEdge(i, j, "WALK", dist);
                graph.addEdge(j, i, "WALK", dist);
            }
        }
    }
}

void App::viewPath(vector<pair<int, string>> path) {
    cout << endl;
    cout << "line: " << path[0].second << endl;
    for (int i = 0; i < path.size() - 1; i++){
        if (path[i].second != path[i+1].second && !path[i+1].second.empty()){
            cout << " -> " << data.getStop(path[i].first) << "-" << data.stopsVector[path[i].first].name << endl;
            cout << " -> " << data.getStop(path[i+1].first) << "-" << data.stopsVector[path[i+1].first].name << endl;
            if (path[i+1].second == "WALK") cout << endl << "Walking:" << endl;
            else if (!path[i+1].second.empty()) cout << endl << "line: " << path[i+1].second << endl;
        }
        else if (path[i+1].second.empty()){
            cout << " -> " << data.getStop(path[i].first) << "-" << data.stopsVector[path[i].first].name << endl;
            cout << " -> " << data.getStop(path[i+1].first) << "-" << data.stopsVector[path[i+1].first].name << endl;
        }
        else{
            cout << " -> " << data.getStop(path[i].first) << "-" << data.stopsVector[path[i].first].name << endl;
        }
    }
}

int App::distance(int src, int dest) {
    double latSrc = data.stopsVector[src].latitude;
    double longSrc = data.stopsVector[src].longitude;
    double latDest = data.stopsVector[dest].latitude;
    double longDest = data.stopsVector[dest].longitude;
    return haversine(latSrc, longSrc, latDest, longDest);
}


int App::haversine(double lat1, double lon1, double lat2, double lon2) {
    const double multiplier = std::pow(10.0, 3);
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    double res = round((rad * c) * multiplier) / multiplier * 1000;
    return (int)res;
}

