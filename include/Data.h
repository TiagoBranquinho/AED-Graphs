//
// Created by alexandre on 22/01/22.
//

#ifndef GRAPHS_AED_DATA_H
#define GRAPHS_AED_DATA_H

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Data{
private:
    std::string filepath = "../dataset/";
    std::string linesFile = "lines.csv";
    std::string stopsFile = "stops.csv";
    std::string linestr = "line";
    std::string filetype = ".csv";
    char sep = '_';

public:
    struct Stop{
        std::string code;
        std::string name;
        std::string zone;
        double latitude;
        double longitude;
    };

    std::map<std::string, std::string> lines;
    std::vector<Stop> stopsVector;
    std::map<int, std::string> stops;
    std::map<std::string, int> nodes;

public:
    Data();
    void readStops();
    void readLines();
    std::vector<std::string> readLine(std::string line, char delim);
    std::vector<std::string> readStop(std::string line, char delim);

    std::vector<std::string> readLinePath(std::string line, std::string direction);
    std::string getLine(std::string code);
    std::string getStop(int node);
    int getNode(std::string stop);

    void clear();
};

#endif //GRAPHS_AED_DATA_H
