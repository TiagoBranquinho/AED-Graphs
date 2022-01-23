#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../include/Data.h"

using testing::Eq;
using namespace std;

TEST(test1, readStopsTest) {
    Data d;
    d.readStops();
    d.readLines();

    cout << "size: " << d.nodes.size() << endl;

    cout << d.getLine("205") << endl;
    cout << d.getStop(78) << endl;
    cout << d.nodes.at("1CDR2") << endl;

    string stop = "1AL5";
    auto it =d.nodes.find(stop);
    if (it == d.nodes.end())
        cout << "stop " << stop << " not found" << endl << endl;
    else
        cout << it->first << " -> " << it->second << endl << endl;

    EXPECT_EQ(it->first, stop);
    EXPECT_EQ(d.getStop(78), "ACST2");
    EXPECT_EQ(d.getNode("1CDR2"), 6);
    EXPECT_EQ(d.getLine("205"), "205 - CAMPANHÃ-CASTELO DO QUEIJO");

    d.clear();
    cout << endl;
    cout << "data class has been cleared!"<< endl;
    cout << endl;
    cout << "size: " << d.nodes.size() << endl;

    try{
        cout << d.getNode("123") << endl;
        cout << d.getLine("205") << endl;
    }catch (std::out_of_range &exception){
        cout << exception.what() << endl;
        cout << "Value not found!" << endl;
    }

    it = d.nodes.find(stop);
    if (it == d.nodes.end())
        cout << "stop " << stop << " not found" << endl;
    else
        cout << it->first << " -> " << it->second << endl;
    EXPECT_EQ(it, d.nodes.end());
}

TEST(test1, readLinePath) {
    Data data;
    vector<string> path = data.readLinePath("1", "1");

    for (auto s : path) {
        cout << " -> " << s;
    }
    cout << endl;

    path = data.readLinePath("1", "0");

    for (auto s : path) {
        cout << " -> " << s;
    }
}