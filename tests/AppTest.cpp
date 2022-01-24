#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../include/App.h"

using testing::Eq;
using namespace std;

TEST(test1, apptest) {
    App app;

    app.createGraph();
    string stop1 = "CMP2";
    //string stop1 = "CMP1";
    //string stop2 = "ARSR1";
    string stop2 = "BFM4";
    int src = app.data.getNode(stop1);
    int dest = app.data.getNode(stop2);

    cout << app.data.getStop(src) << " to " << app.data.getStop(dest) << endl;

    double dist = app.graph.dijkstra_distance(src, dest);
    cout << "distance " << stop1 << "-" << stop2 << " : " << dist  << "m" << endl;

    auto path = app.graph.dijkstra_path(src, dest);

    string line;
    for (auto i : path){
        cout << " -> " << app.data.stopsVector[i.first].name;
    }

}

TEST(test1, distTest) {
    App app;

    string stop1 = "CMP2";
    string stop2 = "NDA1";
    int src = app.data.getNode(stop1);
    int dest = app.data.getNode(stop2);

    int distance = app.distance(src, dest);

    cout << "from " << app.data.stopsVector[src].name << " to " << app.data.stopsVector[dest].name << endl;
    cout << "distance: " << distance << "m" << endl;
}

TEST(test1, distTestWalkPaths) {
    App app;

    app.createGraph();
    app.createWalkPaths(160);

    int cmp2 = app.data.getNode("CMP2");
    int cmp1 = app.data.getNode("CMP1");
    int pbss2 = app.data.getNode("PBSS2");
    cout << "dist cmp1 to cmp2: " << app.distance(cmp1, cmp2) << endl;
    cout << "dist cmp2 to pbss2: " << app.distance(cmp2, pbss2) << endl;
    for (auto i : app.graph.getNodes()[cmp2].adj){
        cout << app.data.getStop(i.dest) << " - " << i.line << " - " << i.distGap << "m ,";
    }
    cout << endl;
    cout << endl;

    /*string stop1 = "CMP2";
    //string stop1 = "CMP1";
    //string stop2 = "ARSR1";
    string stop2 = "BFM4";*/
    string stop1 = "CMP2";
    string stop2 = "GIT1";
    int src = app.data.getNode(stop1);
    int dest = app.data.getNode(stop2);

    cout << app.data.getStop(src) << " to " << app.data.getStop(dest) << endl;

    double dist = app.graph.dijkstra_distance(src, dest);
    cout << "distance " << stop1 << "-" << stop2 << " : " << dist  << "m" << endl;

    auto path = app.graph.dijkstra_path(src, dest);
    app.viewPath(path);
}