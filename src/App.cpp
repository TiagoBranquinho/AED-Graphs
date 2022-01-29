#include "../include/App.h"

#include <iostream>
#include <iomanip>
#include <cmath>

App::App() = default;

void App::loadData() {
    data.readLines();
    data.readStops();
}

void App::createGraphs() {
    data.dayConnector.clear();
    data.dayConnectorInv.clear();
    data.nightConnector.clear();
    data.nightConnectorInv.clear();
    for (int i = 1; i < data.stopsVector.size()-1; i++){
        Node node;
        node.name = data.stopsVector[i].code;
        node.zone = data.stopsVector[i].zone;
        node.line = "";
        dayGraph.addNode(node);
        nightGraph.addNode(node);
        /*dayGraphLines.addNode(node);
        nightGraphLines.addNode(node);
        data.dayConnector.insert({i, i});
        data.nightConnector.insert({i, i});*/
    }
    for (const auto& line : data.lines) {
        vector<string> path0 = data.readLinePath(line.first,"0");
        vector<string> path1 = data.readLinePath(line.first,"1");
        if (line.first.back() == 'M'){
            createLinePath(nightGraph, line.first, path0);
            createLinePath(nightGraph, line.first, path1);
            createLinePath(nightGraphLines, data.nightConnector, data.nightConnectorInv, line.first, path0);
            createLinePath(nightGraphLines, data.nightConnector, data.nightConnectorInv, line.first, path1);
        } else {
            createLinePath(dayGraph, line.first, path0);
            createLinePath(dayGraph, line.first, path1);
            createLinePath(dayGraphLines, data.dayConnector, data.dayConnectorInv, line.first, path0);
            createLinePath(dayGraphLines, data.dayConnector, data.dayConnectorInv, line.first, path1);
        }
    }
}


void App::createLinePath(GraphLines &graph, map<int, int> &connector, map<int, vector<int>> &inverter, std::string line, std::vector<std::string> path) {
    if (path.empty()) return;

    for (int i = 0; i < path.size() - 1; i++) {
        int src = data.getNode(path[i]);
        int dest = data.getNode(path[i + 1]);

        Node srcNode, destNode;
        srcNode.name = data.stopsVector[src].code;
        srcNode.zone = data.stopsVector[src].zone;
        srcNode.line = line;
        destNode.name = data.stopsVector[dest].code;
        destNode.zone = data.stopsVector[dest].zone;
        destNode.line = line;

        int srcLN = graph.addNode(srcNode);
        int destLN = graph.addNode(destNode);
        connector.insert({srcLN, src});
        connector.insert({destLN, dest});
        inverter[src].push_back(srcLN);
        inverter[dest].push_back(destLN);

        graph.addEdge(srcLN, destLN, line, 0);

        for (int j = 1; j < graph.getNodes().size()-1; j++) {
            int nd = connector.at(j);
            //int nd = data.getNode(graph.getNodes()[n].name);
            string nodeName = graph.getNodes()[j].name;
            string nodeLine = graph.getNodes()[j].line;

            if (srcNode.name == nodeName && srcNode.line != nodeLine && !srcNode.line.empty() && !nodeLine.empty()){
                graph.addEdge(srcLN,j,srcNode.line, 1);
                graph.addEdge(j,srcLN,nodeLine, 1);
            }
            if (destNode.name == nodeName && destNode.line != nodeLine && !destNode.line.empty() && !nodeLine.empty()){
                graph.addEdge(destLN,j,destNode.line, 1);
                graph.addEdge(j,destLN,nodeLine, 1);
            }
            if (distance(src, nd) < maxWalkDist && srcNode.name != nodeName && !srcNode.line.empty() && !nodeLine.empty()){
                int w = srcNode.line!=nodeLine;
                graph.addEdge(srcLN, j, "WALK", 1);
                graph.addEdge(j, srcLN, "WALK", 1);
            }
            if (distance(nd, dest) < maxWalkDist && destNode.name != nodeName && !destNode.line.empty() && !nodeLine.empty()){
                int w = destNode.line!=nodeLine;
                graph.addEdge(destLN, j, "WALK", 1);
                graph.addEdge(j, destLN, "WALK", 1);
            }
        }
    }
}

void App::createLinePath(GraphGN &graph, string line, vector<string> path) {
    if (path.empty()) return;
    for (int i = 0; i < path.size() - 1; i++) {
        int src = data.getNode(path[i]);
        int dest = data.getNode(path[i+1]);
        graph.addEdge(src, dest, line, distance(src, dest));
    }
}

void App::createWalkPaths() {
    size_t size = data.stopsVector.size();
    for (int i = 0; i < size; i++){
        for (int j = i+1; j < size - 1; j++){
            int dist = distance(i,j);
            if (dist <= maxWalkDist){
                dayGraph.addEdge(i, j, "WALK", dist);
                dayGraph.addEdge(j, i, "WALK", dist);
                nightGraph.addEdge(i, j, "WALK", dist);
                nightGraph.addEdge(j, i, "WALK", dist);
            }
        }
    }
}

void App::viewPath(vector<pair<int, string>> path, string time) {
    if (path.empty()){
        cout << "No path available." << endl;
        return;
    }
    if (!time.empty()){
        for (auto& stop : path){
            if (time=="day") stop.first = data.dayConnector.at(stop.first);
            if (time=="night") stop.first = data.nightConnector.at(stop.first);
        }
    }
    cout << endl;
    cout << (path[0].second=="WALK"? "Walking: ":"line: "+path[0].second) << endl;
    for (int i = 0; i < path.size() - 1; i++){
        string stop1 = data.getStop(path[i].first) + "-" + data.stopsVector[path[i].first].name;
        string zone1 = data.stopsVector[path[i].first].zone;
        string stop2 = data.getStop(path[i+1].first) + "-" + data.stopsVector[path[i+1].first].name;
        string zone2 = data.stopsVector[path[i+1].first].zone;
        int width = 37;
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
    resetGraphs();
}

int App::addLocalNode(pair<double, double> local, string name, int direction) {
    Node node; node.name = name;
    Stop stop; stop.name = name;
    stop.latitude = local.first;
    stop.longitude = local.second;

    int index = dayGraph.addNode(node);
    data.stopsVector.push_back(stop);
    data.stops.insert({index, name});
    data.nodes.insert({name, index});
    addWalkPathsToNode(index, direction);
    return index;
}

void App::removeLocalNode(int node) {
    string code = data.getStop(node);
    dayGraph.removeNode(node);
    data.stopsVector.erase(data.stopsVector.begin()+node);
    data.stops.erase(node);
    data.nodes.erase(code);
}

void App::addWalkPathsToNode(int node, int direction) {
    for (int i = 0; i < dayGraph.getNodes().size(); i++){
        int dist = distance(node, i);
        if (dist <= maxWalkDist){
            if (direction) dayGraph.addEdge(i, node, "WALK", dist);
            else dayGraph.addEdge(node, i, "WALK", dist);
        }
    }
}

GraphGN App::getGraph() {
    return dayGraph;
}

Data App::getData() {
    return data;
}

void App::resetGraphs() {
    dayGraph = GraphGN();
    nightGraph = GraphGN();
    dayGraphLines = GraphLines();
    nightGraphLines = GraphLines();
    createGraphs();
    createWalkPaths();
    //connectLinesWalks(dayGraphLines);
    //connectLinesWalks(nightGraphLines);
}

