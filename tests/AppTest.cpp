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

    double dist = app.graph.dijkstraDistanceDS(src, dest);
    cout << "distance " << stop1 << "-" << stop2 << " : " << dist  << "m" << endl;

    auto path = app.graph.dijkstraPathDS(src, dest);

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
    app.createWalkPaths(150);

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

    //string stop1 = "CMP2";
    //string stop1 = "CMP1";
    string stop2 = "ARSR1";
    //string stop2 = "BFM4";
    string stop1 = "CMP2";
    //string stop2 = "GIT1";
    int src = app.data.getNode(stop1);
    int dest = app.data.getNode(stop2);

    cout << app.data.getStop(src) << " to " << app.data.getStop(dest) << endl;

    double dist = app.graph.dijkstraDistanceDS(src, dest);
    cout << "distance " << stop1 << "-" << stop2 << " : " << dist  << "m" << endl;

    auto path = app.graph.dijkstraPathDS(src, dest);
    app.viewPath(path);
}

TEST(test1, distLinesTest) {
    App app;

    app.createGraph();
    app.createWalkPaths(100);

    int PBSS2 = app.data.getNode("PBSS2");
    int PBSS4 = app.data.getNode("PBSS4");
    cout << "dist PBSS2 to PBSS4: " << app.distance(PBSS2, PBSS4) << endl << endl;

    //string stop2 = "ARSR1";
    /*string stop2 = "RFZ1";
    string stop1 = "CMP2";*/
    string stop1 = "CMP2";
    string stop2 = "RCON";
    int src = app.data.getNode(stop1);
    int dest = app.data.getNode(stop2);

    cout << app.data.getStop(src) << " to " << app.data.getStop(dest) << endl;
    cout << "number of lines: " << app.graph.dijkstraDistanceLN(src, dest) << endl;

    auto path = app.graph.dijkstraPathLN(src, dest);
    app.viewPath(path);
}