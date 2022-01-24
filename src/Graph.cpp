#include "../include/Graph.h"
#include <climits>
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

list<pair<int, string>> Graph::dijkstraPath(int a, int b) {
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
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
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

    while (q.getSize()>0) {
        int u = q.removeMin();
        nodes[u].visited = true;
        //cout << "In Node " << nodes[u].name << " lines = " << nodes[u].lineChanges << endl;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = nodes[u].lineCon != e.line; // considering walking is a line change
            /*if (e.line == "WALK") w = 0;
            else w = nodes[u].lineCon != e.line;*/ // considering walking isn't a line change

            //cout << "Node " << nodes[v].name << " visited : " << nodes[v].visited << endl;
            //cout << "Weight " << w << endl;
            if (!nodes[v].visited && nodes[u].lineChanges + w <= nodes[v].lineChanges) {
                //cout << "Node " << nodes[v].name << " with " << nodes[v].lineChanges << " changed" << endl;
                nodes[v].lineChanges = nodes[u].lineChanges + w;
                q.decreaseKey(v, nodes[v].lineChanges);
                nodes[v].pred = u;
                nodes[v].lineCon = e.line;
                //cout << "AFTER -> Node " << nodes[v].name << " with " << nodes[v].lineChanges << " changed" << endl;
            }
        }
        //cout << endl;
    }
}

void Graph::dijkstraZones(int s) {

}

int Graph::dijkstraDistanceDS(int a, int b) {
    dijkstraDist(a);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}

vector<pair<int,string>> Graph::dijkstraPathDS(int a, int b) {
    dijkstraDist(a);
    list<pair<int,string>> path;
    if (nodes[b].dist == INF) return {};
    path.emplace_back(b,"");
    int v = b;
    while (v != a) {
        string line = nodes[v].lineCon;
        v = nodes[v].pred;
        path.push_front({v,line});
    }
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
    list<pair<int,string>> path = dijkstraPath(a,b);
    vector<pair<int,string>> res(path.begin(), path.end());
    return res;
}
