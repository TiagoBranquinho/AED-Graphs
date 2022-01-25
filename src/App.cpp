#include "../include/App.h"

#include <iostream>
#include <iomanip>
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
        graph.getNodes()[i].zone = data.stopsVector[i].zone;
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
    if (path.empty()){
        cout << "No path available." << endl;
        return;
    }
    cout << endl;
    cout << "line: " << path[0].second << endl;
    for (int i = 0; i < path.size() - 1; i++){
        string stop1 = data.getStop(path[i].first) + "-" + data.stopsVector[path[i].first].name;
        string zone1 = data.stopsVector[path[i].first].zone;
        string stop2 = data.getStop(path[i+1].first) + "-" + data.stopsVector[path[i+1].first].name;
        string zone2 = data.stopsVector[path[i+1].first].zone;
        int width = 35;
        if (path[i].second != path[i+1].second && !path[i+1].second.empty()){
            cout << std::left << " -> " << setw(width) << stop1 << zone1 << endl;
            cout << std::left << " -> " << setw(width) << stop2 << zone2 << endl;
            if (path[i+1].second == "WALK") cout << endl << "Walking:" << endl;
            else if (!path[i+1].second.empty()) cout << endl << "line: " << path[i+1].second << endl;
        }
        else if (path[i+1].second.empty()){
            cout << std::left << " -> " << setw(width) << stop1 << zone1 << endl;
            cout << std::left << " -> " << setw(width) << stop2 << zone2 << endl;
        }
        else{
            cout << std::left << " -> " << setw(width) << stop1 << zone1 << endl;
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

int App::getMaxWalkDist() {
    return maxWalkDist;
}

void App::setMaxWalkDist(int dist) {
    maxWalkDist = dist;
}

int App::addLocalNode(pair<double, double> local, string name, int direction) {
    graph.addNodeN();
    int index = (int) graph.getNodes().size();
    string nodeName = name + " lat: " + to_string(local.first) + " long: " + to_string(local.second);
    graph.getNodes().push_back({{}, 0,0,0,0,0,false,"", nodeName, ""});
    data.stopsVector.push_back({"", nodeName, "", local.first, local.second});
    data.stops.insert({index, nodeName});
    data.nodes.insert({nodeName, index});
    addWalkPathsToNode(index, direction);
    return index;
}

void App::removeLocalNode(int node) {
    string code = data.getStop(node);
    graph.getNodes().erase(graph.getNodes().begin()+node);
    data.stopsVector.erase(data.stopsVector.begin()+node);
    data.stops.erase(node);
    data.nodes.erase(code);
    graph.removeNodeN();
}

void App::addWalkPathsToNode(int node, int direction) {
    for (int i = 0; i < graph.getNodes().size(); i++){
        int dist = distance(node, i);
        if (dist <= maxWalkDist){
            if (direction) graph.addEdge(i,node,"WALK", dist);
            else graph.addEdge(node,i,"WALK", dist);
        }
    }
}
