//
// Created by alexandre on 22/01/22.
//

#include "../include/Data.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Data::Data() = default;

void Data::readStops() {
    std::ifstream file(filepath + stopsFile);
    string fileline;

    if (file.is_open()){
        getline(file, fileline);
        int count = 0;

        while (getline(file, fileline)) {
            count++;
            vector<string> values = readStop(fileline, ',');
            Stop stop;
            int i = 0;
            stop.code = values.at(i++);
            stop.name = values.at(i++);
            stop.zone = values.at(i++);
            stop.latitude = stod(values.at(i++));
            stop.longitude = stod(values.at(i++));

            stopsVector.push_back(stop);
            stops.insert({count, stop.code});
            nodes.insert({stop.code, count});
        }
        file.close();
    }
}

vector<string> Data::readStop(std::string fileLine, char delim) {
    string value;
    stringstream ss(fileLine);
    vector<string> values;
    for (int i = 0; i < 5; i++){
        getline(ss, value, delim);
        values.push_back(value);
    }
    return values;
}

void Data::readLines() {
    std::ifstream file(filepath + linesFile);
    string fileLine;

    if (file.is_open()){
        getline(file, fileLine);
        while (getline(file, fileLine)) {
            vector<string> values = readLine(fileLine, ',');
            lines.insert({values[0], values[1]});
        }
        file.close();
    }

}

std::vector<std::string> Data::readLine(std::string fileLine, char delim) {
    string value;
    stringstream ss(fileLine);
    vector<string> values;
    for (int i = 0; i < 2; i++){
        getline(ss, value, delim);
        values.push_back(value);
    }
    return values;
}

vector<string> Data::readLinePath(std::string line, string direction) {
    vector<string> linepath;
    string filename = linestr + sep + line + sep + direction + filetype;
    ifstream file(filepath + filename);

    int linesize;
    string stopname;
    if (file.is_open()){
        file >> linesize;
        for (int i = 0; i < linesize; i++){
            file >> stopname;
            linepath.push_back(stopname);
        }
        file.close();
    }
    return linepath;
}

std::string Data::getLine(std::string code) {
    return lines.at(code);
}

int Data::getNode(std::string stop) {
    return nodes.at(stop);
}

std::string Data::getStop(int node) {
    return stops.at(node);
}

void Data::clear() {
    lines.clear();
    stops.clear();
    nodes.clear();
    stopsVector.clear();
}
