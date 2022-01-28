#include "../include/GraphLines.h"
#include "../include/MinHeap.h"

using namespace std;

void GraphLines::dijkstraLines(int s) {
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
            int w = e.distGap;
            //int w = nodes[u].lineCon != e.line; // considering walking is a line change
            /*if (e.line == "WALK" || (nodes[u].lineCon=="s" && e.line=="WALK")) w = 0;
            else w = 1; // considering walking isn't a line change*/
            //cout << "Node " << nodes[v].name << " visited : " << nodes[v].visited << endl;
            //cout << "Weight " << w << endl;
            if (!nodes[v].visited && nodes[u].lineChanges + w < nodes[v].lineChanges && !(e.line == "WALK" && nodes[u].lineCon == "WALK")) {
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

int GraphLines::dijkstraDistanceLN(int a, int b) {
    dijkstraLines(a);
    if (nodes[b].lineChanges == INF) return -1;
    return nodes[b].lineChanges;
}

vector<pair<int, string>> GraphLines::dijkstraPathLN(int a, int b) {
    dijkstraLines(a);
    if (nodes[b].lineChanges == INF) return {};
    list<pair<int,string>> path = buildPath(a, b);
    vector<pair<int,string>> res(path.begin(), path.end());
    return res;
}
