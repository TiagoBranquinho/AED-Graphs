#include "../include/Graph.h"
#include <climits>
#include <queue>
#include <algorithm>

#define INF (INT_MAX/2)

Graph::Graph() = default;

Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

vector<Graph::Node> &Graph::getNodes() {
    return nodes;
}

void Graph::addEdge(int src, int dest, const string& line, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}

list<pair<int, string>> Graph::buildPath(int a, int b) {
    list<pair<int,string>> path;
    path.emplace_back(b,"");
    int v = b;
    while (v != a) {
        string line = nodes[v].lineCon;
        v = nodes[v].pred;
        path.push_front({v,line});
    }
    return path;
}

list<pair<int, string>> Graph::backtraceDijkstraLines(int a, int b, int dist){
    int maxChanges = dist;
    int dest = b;
    while (dest != a){
        int changes = nodes[dest].lineChanges;
        for (const auto& line : nodes[dest].lineCons) {
            int src = line.first;
            if (nodes[src].lineChanges <= changes){
                dest = src;
                break;
            }
        }
    }
    return buildPath(a,b);
}

void Graph::bfsStops(int s) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(s);
    nodes[s].visited = true;
    nodes[s].stopChanges = 1;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        //cout << nodes[u].name << endl; // show node order
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            if (!nodes[v].visited && !(e.line == "WALK" && nodes[u].lineCon == "WALK")) {
                q.push(v);
                nodes[v].visited = true;
                nodes[v].stopChanges = nodes[u].stopChanges + 1;
                nodes[v].pred = u;
                nodes[v].lineCon = e.line;
            }
        }
    }
}


void Graph::dijkstraDist(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].dist = INF;
        nodes[v].visited = false;
        nodes[v].lineCon = "";
        q.insert(v, INF);
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;

    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].distGap << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.distGap;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist && !(e.line == "WALK" && nodes[u].lineCon == "WALK")) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);

                nodes[v].pred = u;
                nodes[v].lineCon = e.line;
            }
        }
    }
}

void Graph::dijkstraLines(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].lineChanges = INF;
        nodes[v].visited = false;
        nodes[v].lineCon = "";
        q.insert(v, INF);
    }
    nodes[s].lineChanges = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    nodes[s].lineCon = "s";

    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u].visited = true;
        //cout << "In Node " << nodes[u].name << " lines = " << nodes[u].lineChanges << endl;
        for (auto e : nodes[u].adj) {
            int v = e.dest; int w;
            //int w = nodes[u].lineCon != e.line; // considering walking is a line change
            if (e.line == "WALK" || (nodes[u].lineCon=="s" && e.line=="WALK")) w = 0;
            else if (checkBackLines(u,e)) w = 0;
            else w = 1; // considering walking isn't a line change

            //cout << "Node " << nodes[v].name << " visited : " << nodes[v].visited << endl;
            //cout << "Weight " << w << endl;
            if (!nodes[v].visited && nodes[u].lineChanges + w <= nodes[v].lineChanges && !(e.line == "WALK" && nodes[u].lineCon == "WALK")) {
                //cout << "Node " << nodes[v].name << " with " << nodes[v].lineChanges << " changed" << endl;
                nodes[v].lineChanges = nodes[u].lineChanges + w;
                q.decreaseKey(v, nodes[v].lineChanges);
                nodes[v].pred = u;
                nodes[v].lineCon = e.line;
                nodes[v].lineCons.emplace_back(u,e.line);
                if (nodes[u].lineChanges + w < nodes[v].lineChanges){
                    nodes[v].lineCons = {{u,e.line}};
                }
                //cout << "AFTER -> Node " << nodes[v].name << " with " << nodes[v].lineChanges << " changed" << endl;
            }
        }
        //cout << endl;
    }
}

void Graph::dijkstraZones(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].zoneChanges = INF;
        nodes[v].visited = false;
        nodes[v].lineCon = "";
        q.insert(v, INF);
    }
    nodes[s].zoneChanges = 1;
    q.decreaseKey(s, 1);
    nodes[s].pred = s;

    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u].visited = true;
        //cout << "In Node " << nodes[u].name << " " << nodes[u].zone << " lines = " << nodes[u].zoneChanges << endl;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = nodes[u].zone != nodes[v].zone;
            //cout << "Node " << nodes[v].name << " " << nodes[v].zone << " visited : " << nodes[v].visited << endl;
            //cout << "Weight " << w << endl;
            if (!nodes[v].visited && nodes[u].zoneChanges + w < nodes[v].zoneChanges && !(e.line == "WALK" && nodes[u].lineCon == "WALK")) {
                //cout << "Node " << nodes[v].name << " " << nodes[v].zone << " with " << nodes[v].zoneChanges << " changed" << endl;
                nodes[v].zoneChanges = nodes[u].zoneChanges + w;
                q.decreaseKey(v, nodes[v].zoneChanges);
                nodes[v].pred = u;
                nodes[v].lineCon = e.line;
                //cout << "AFTER -> Node " << nodes[v].name << " " << nodes[v].zone << " with " << nodes[v].zoneChanges << " changed" << endl;
            }
        }
        //cout << endl;
    }
}

int Graph::bfsDistanceST(int a, int b) {
    bfsStops(a);
    if (nodes[b].stopChanges == 0) return -1;
    return nodes[b].stopChanges;
}

vector<pair<int, string>> Graph::bfsPathST(int a, int b) {
    bfsStops(a);
    if (nodes[b].stopChanges == 0) return {};
    list<pair<int,string>> path = buildPath(a, b);
    vector<pair<int, string>> res(path.begin(), path.end());
    return res;
}

int Graph::dijkstraDistanceDS(int a, int b) {
    dijkstraDist(a);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}

vector<pair<int,string>> Graph::dijkstraPathDS(int a, int b) {
    dijkstraDist(a);
    if (nodes[b].dist == INF) return {};
    list<pair<int,string>> path = buildPath(a, b);
    vector<pair<int,string>> res(path.begin(), path.end());
    return res;
}

int Graph::dijkstraDistanceLN(int a, int b) {
    dijkstraLines(a);
    if (nodes[b].lineChanges == INF) return -1;
    return nodes[b].lineChanges;
}

vector<pair<int, string>> Graph::dijkstraPathLN(int a, int b) {
    dijkstraLines(a);
    if (nodes[b].lineChanges == INF) return {};
    list<pair<int,string>> path = buildPath(a, b);
    vector<pair<int,string>> res(path.begin(), path.end());
    return res;
}

int Graph::dijkstraDistanceZN(int a, int b) {
    dijkstraZones(a);
    if (nodes[b].zoneChanges == INF) return -1;
    return nodes[b].zoneChanges;
}

vector<pair<int, string>> Graph::dijkstraPathZN(int a, int b) {
    dijkstraZones(a);
    if (nodes[b].zoneChanges == INF) return {};
    list<pair<int,string>> path = buildPath(a, b);
    vector<pair<int,string>> res(path.begin(), path.end());
    return res;
}

void Graph::addNodeN() {
    n++;
}

void Graph::removeNodeN() {
    n--;
}

bool Graph::checkBackLines(int u, const Edge& e) {
    for (const auto& backLine :nodes[u].lineCons)
        if (backLine.second == e.line)
            return true;
    return false;
}

