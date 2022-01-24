#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Graph.h"
#include <iostream>

using testing::Eq;

TEST(test1, dijkstraDistance) {
    Graph g1(9, false);
    g1.addEdge(1, 2,"", 5);
    g1.addEdge(1, 7,"", 3);
    g1.addEdge(2, 3,"", 2);
    g1.addEdge(2, 6,"", 15);
    g1.addEdge(2, 4,"", 4);
    g1.addEdge(3, 6,"", 3);
    g1.addEdge(3, 4,"", 1);
    g1.addEdge(3, 8,"", 9);
    g1.addEdge(4, 5,"", 8);
    g1.addEdge(4, 9,"", 7);
    g1.addEdge(5, 6,"", 5);
    g1.addEdge(6, 7,"",8);
    g1.addEdge(8, 9,"",6);

    for (auto i : g1.dijkstraPathDS(1, 9))
        cout << " > " << i.first;

    EXPECT_EQ(5, g1.dijkstraDistanceDS(1, 2));
    EXPECT_EQ(2, g1.dijkstraDistanceDS(2, 3));
    EXPECT_EQ(3, g1.dijkstraDistanceDS(1, 7));
    EXPECT_EQ(8, g1.dijkstraDistanceDS(6, 7));
    EXPECT_EQ(3, g1.dijkstraDistanceDS(3, 6));
    EXPECT_EQ(3, g1.dijkstraDistanceDS(2, 4));
    EXPECT_EQ(5, g1.dijkstraDistanceDS(2, 6));
    EXPECT_EQ(5, g1.dijkstraDistanceDS(5, 6));
    EXPECT_EQ(1, g1.dijkstraDistanceDS(3, 4));
    EXPECT_EQ(11, g1.dijkstraDistanceDS(2, 8));
    EXPECT_EQ(15, g1.dijkstraDistanceDS(1, 9));






}
