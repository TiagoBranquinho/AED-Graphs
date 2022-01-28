#include "../include/Graph.h"

#include <string>
#include <algorithm>

using namespace std;

Graph::Graph(bool hasDir): hasDir(hasDir){}

vector<Node> &Graph::getNodes() {
    return nodes;
}

int Graph::addNode(const Node &node) {
    int index = (int)nodes.size();
    for (int i=1; i <= n; i++)
        if(nodes[i].name==node.name && nodes[i].line==node.line)
            return i;
    nodes.push_back(node);
    n++;
    return index;
}

void Graph::removeNode(int node) {
    nodes.erase(nodes.begin()+node);
    n--;
}

std::list<std::pair<int, std::string>> Graph::buildPath(int a, int b) {
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

void Graph::addEdge(int src, int dest, const string &line, int weight) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    nodes[src].adj.push_back({dest, weight, line});
    if (!hasDir) nodes[dest].adj.push_back({src, weight, line});
}

