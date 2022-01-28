#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../include/App.h"

using testing::Eq;
using namespace std;

TEST(test1, apptest) {
    App app;

    app.createGraphs();
    string stop1 = "CMP2";
    //string stop1 = "CMP1";
    //string stop2 = "ARSR1";
    string stop2 = "BFM4";
    int src = app.getData().getNode(stop1);
    int dest = app.getData().getNode(stop2);

    cout << app.getData().getStop(src) << " to " << app.getData().getStop(dest) << endl;

    double dist = app.getGraph().dijkstraDistanceDS(src, dest);
    cout << "distance " << stop1 << "-" << stop2 << " : " << dist  << "m" << endl;

    auto path = app.getGraph().dijkstraPathDS(src, dest);

    string line;
    for (auto i : path){
        cout << " -> " << app.getData().stopsVector[i.first].name;
    }

}

TEST(test1, distTest) {
    App app;

    string stop1 = "CMP2";
    string stop2 = "NDA1";
    int src = app.getData().getNode(stop1);
    int dest = app.getData().getNode(stop2);

    int distance = app.distance(src, dest);

    cout << "from " << app.getData().stopsVector[src].name << " to " << app.getData().stopsVector[dest].name << endl;
    cout << "distance: " << distance << "m" << endl;
}

TEST(test1, distTestWalkPaths) {
    App app;

    app.createGraphs();
    app.createWalkPaths(150);

    int cmp2 = app.getData().getNode("CMP2");
    int cmp1 = app.getData().getNode("CMP1");
    int pbss2 = app.getData().getNode("PBSS2");
    cout << "dist cmp1 to cmp2: " << app.distance(cmp1, cmp2) << endl;
    cout << "dist cmp2 to pbss2: " << app.distance(cmp2, pbss2) << endl;
    for (auto i : app.getGraph().getNodes()[cmp2].adj){
        cout << app.getData().getStop(i.dest) << " - " << i.line << " - " << i.distGap << "m ,";
    }
    cout << endl;
    cout << endl;

    //string stop1 = "CMP2";
    //string stop1 = "CMP1";
    string stop2 = "ARSR1";
    //string stop2 = "BFM4";
    string stop1 = "CMP2";
    //string stop2 = "GIT1";
    int src = app.getData().getNode(stop1);
    int dest = app.getData().getNode(stop2);

    cout << app.getData().getStop(src) << " to " << app.getData().getStop(dest) << endl;

    double dist = app.getGraph().dijkstraDistanceDS(src, dest);
    cout << "distance " << stop1 << "-" << stop2 << " : " << dist  << "m" << endl;

    auto path = app.getGraph().dijkstraPathDS(src, dest);
    app.viewPath(path, "day");
}

TEST(test1, distLinesTest) {
    App app;
    app.loadData();
    app.setMaxWalkDist(200);
    app.createGraphs();
    app.connectLinesWalks(app.dayGraphLines);
    //app.connectLinesWalks(app.nightGraphLines);

    int PBSS2 = app.getData().getNode("PBSS2");
    int PBSS4 = app.getData().getNode("PBSS4");
    cout << "dist PBSS2 to PBSS4: " << app.distance(PBSS2, PBSS4) << endl << endl;

    //string stop2 = "ARSR1";
    /*string stop2 = "RFZ1";
    string stop1 = "CMP2";*/
    string stop1 = "CMP2";
    string stop2 = "HMBC2";
    int src = app.getData().getNode(stop1);
    int dest = app.getData().getNode(stop2);

    cout << app.getData().getStop(src) << " to " << app.getData().getStop(dest) << endl;
    cout << "number of lines: " << app.dayGraphLines.dijkstraDistanceLN(src, dest) << endl;

    auto path = app.dayGraphLines.dijkstraPathLN(src, dest);
    app.viewPath(path, "day");
}

TEST(test1, distZonesTest) {
    App app;

    app.createGraphs();
    app.createWalkPaths(100);

    int PBSS2 = app.getData().getNode("PBSS2");
    int PBSS4 = app.getData().getNode("PBSS4");
    cout << "dist PBSS2 to PBSS4: " << app.distance(PBSS2, PBSS4) << endl << endl;

    //string stop2 = "ARSR1";
    /*string stop2 = "RFZ1";
    string stop1 = "CMP2";*/
    string stop1 = "CMP2";
    string stop2 = "BCM4";
    int src = app.getData().getNode(stop1);
    int dest = app.getData().getNode(stop2);

    cout << app.getData().getStop(src) << " to " << app.getData().getStop(dest) << endl;
    cout << "number of zones: " << app.getGraph().dijkstraDistanceZN(src, dest) << endl;

    auto path = app.getGraph().dijkstraPathZN(src, dest);
    app.viewPath(path, "day");
}

TEST(test1, distStopsTest) {
    App app;

    app.createGraphs();
    app.createWalkPaths(100);

    int PBSS2 = app.getData().getNode("PBSS2");
    int PBSS4 = app.getData().getNode("PBSS4");
    cout << "dist PBSS2 to PBSS4: " << app.distance(PBSS2, PBSS4) << endl << endl;

    //string stop2 = "ARSR1";
    /*string stop2 = "RFZ1";
    string stop1 = "CMP2";*/
    string stop1 = "CMP2";
    string stop2 = "CMP1";
    int src = app.getData().getNode(stop1);
    int dest = app.getData().getNode(stop2);

    cout << app.getData().getStop(src) << " to " << app.getData().getStop(dest) << endl;
    cout << "number of stops: " << app.getGraph().bfsDistanceST(src, dest) << endl;

    auto path = app.getGraph().bfsPathST(src, dest);
    app.viewPath(path, "day");
}

TEST(test1, coordsLocalsTests) {
    App app;
    int maxDist = 200;

    app.createGraphs();
    app.createWalkPaths(maxDist);
    app.setMaxWalkDist(maxDist);

    int src = app.addLocalNode({41.145104, -8.610857},"My Position", 0);

    string stop1 = "CMP2";
    int dest = app.getData().getNode(stop1);

    cout << app.getData().getStop(src) << " to " << app.getData().getStop(dest) << endl;
    cout << "number of stops: " << app.getGraph().bfsDistanceST(src, dest) << endl;

    auto path = app.getGraph().bfsPathST(src, dest);
    app.viewPath(path, "day");

    cout << "BEFORE stop map size " << app.getData().stops.size() << endl;
    cout << "BEFORE nodes map size " << app.getData().nodes.size() << endl;
    app.removeLocalNode(src);
    cout << "AFTER stop map size " << app.getData().stops.size() << endl;
    cout << "AFTER nodes map size " << app.getData().nodes.size() << endl;
}

TEST(test1, coordsSRCandDESTTests) {
    App app;
    int maxDist = 100;

    app.createGraphs();
    app.createWalkPaths(maxDist);
    app.setMaxWalkDist(maxDist);

    int src = app.addLocalNode({41.145104, -8.610857},"My Position", 0);
    int dest = app.addLocalNode({41.150147, -8.602150},"Destination", 1);

    cout << app.getData().getStop(src) << " to " << app.getData().getStop(dest) << endl;
    cout << "number of lines: " << app.getGraph().dijkstraDistanceDS(src, dest) << endl;

    auto path = app.getGraph().dijkstraPathDS(src, dest);
    app.viewPath(path, "day");
    app.removeLocalNode(src);
}