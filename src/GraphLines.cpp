#include "../include/GraphLines.h"
#include "../include/MinHeap.h"

#include <iostream>

using namespace std;

void GraphLines::dijkstraLines(vector<int> s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].lineChanges = INF;
        nodes[v].visited = false;
        nodes[v].lineCon = "";
        q.insert(v, INF);
    }
    for (auto src : s){
        nodes[src].lineChanges = 0;
        q.decreaseKey(src, 0);
        nodes[src].pred = -1;
    }

    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.distGap;
            if (!nodes[v].visited && nodes[u].lineChanges + w < nodes[v].lineChanges && !(e.line == "WALK" && nodes[u].lineCon == "WALK")) {
                nodes[v].lineChanges = nodes[u].lineChanges + w;
                q.decreaseKey(v, nodes[v].lineChanges);
                nodes[v].pred = u;
                nodes[v].lineCon = e.line;
            }
        }
    }
}

int GraphLines::dijkstraDistanceLN(vector<int> a, vector<int> b) {
    dijkstraLines(a);
    int dest = minDest(b);
    if (nodes[dest].lineChanges == INF) return -1;
    return nodes[dest].lineChanges;
}

vector<pair<int, string>> GraphLines::dijkstraPathLN(vector<int> a, vector<int> b) {
    dijkstraLines(a);
    int dest = minDest(b);
    if (nodes[dest].lineChanges == INF) return {};
    list<pair<int,string>> path;
    path.emplace_back(dest,"");
    int v = dest;
    while (v != -1) {
        string line = nodes[v].lineCon;
        v = nodes[v].pred;
        path.push_front({v,line});
    }
    path.erase(path.begin());
    vector<pair<int,string>> res(path.begin(), path.end());
    return res;
}

int GraphLines::minDest(std::vector<int> dest) {
    int node = dest[0];
    int minimum = nodes[dest[0]].lineChanges;
    for (int i : dest){
        if(minimum > nodes[i].lineChanges){
            minimum = nodes[i].lineChanges;
            node = i;
        }
    }
    return node;
}
