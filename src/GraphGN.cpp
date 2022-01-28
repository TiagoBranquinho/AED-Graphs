#include "../include/GraphGN.h"

#include <queue>

void GraphGN::bfsStops(int s) {
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


void GraphGN::dijkstraDist(int s) {
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

void GraphGN::dijkstraZones(int s) {
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

int GraphGN::bfsDistanceST(int a, int b) {
    bfsStops(a);
    if (nodes[b].stopChanges == 0) return -1;
    return nodes[b].stopChanges;
}

vector<pair<int, string>> GraphGN::bfsPathST(int a, int b) {
    bfsStops(a);
    if (nodes[b].stopChanges == 0) return {};
    list<pair<int,string>> path = buildPath(a, b);
    vector<pair<int, string>> res(path.begin(), path.end());
    return res;
}

int GraphGN::dijkstraDistanceDS(int a, int b) {
    dijkstraDist(a);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}

vector<pair<int,string>> GraphGN::dijkstraPathDS(int a, int b) {
    dijkstraDist(a);
    if (nodes[b].dist == INF) return {};
    list<pair<int,string>> path = buildPath(a, b);
    vector<pair<int,string>> res(path.begin(), path.end());
    return res;
}

int GraphGN::dijkstraDistanceZN(int a, int b) {
    dijkstraZones(a);
    if (nodes[b].zoneChanges == INF) return -1;
    return nodes[b].zoneChanges;
}

vector<pair<int, string>> GraphGN::dijkstraPathZN(int a, int b) {
    dijkstraZones(a);
    if (nodes[b].zoneChanges == INF) return {};
    list<pair<int,string>> path = buildPath(a, b);
    vector<pair<int,string>> res(path.begin(), path.end());
    return res;
}
