#ifndef GRAPHS_AED_DATA_H
#define GRAPHS_AED_DATA_H

#include "structs.h"

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
    std::map<std::string, std::string> lines; /** Maps the line string code to the matching line description string */
    std::vector<Stop> stopsVector; /** Vector of all stops with all their data, the vector indexes match the correspondent integer node identifiers, so that we can easily access them */
    std::map<int, std::string> stops;/** Maps the node integer identifier to the matching stop code string */
    std::map<std::string, int> nodes; /** Maps the stops code string to the node integer identifier */
    std::map<int, int> nightConnector; /** Connector the maps the node identifiers of the GraphLines to the correspondent node in the GraphGN (night mode)  */
    std::map<int, std::vector<int>> nightInverter; /** Inverter the maps the node identifiers of the GraphGN to the correspondent vector of nodes in the GraphLines (night mode) */
    std::map<int, int> dayConnector; /** Connector the maps the node identifiers of the GraphLines to the correspondent node in the GraphGN (day mode)  */
    std::map<int, std::vector<int>> dayInverter; /** Inverter the maps the node identifiers of the GraphGN to the correspondent vectors of node in the GraphLines (day mode)  */

public:
    /**
     * Data class default constructor
     */
    Data();
    /**
     * Reads all stops from the stops file and saves that data
     */
    void readStops();
    /**
     * Reads all bus lines from the lines file and from each line file in specific and saves that data
     */
    void readLines();
    /**
     * Reads a line from the string passed in the argument, splitting it using the delimitation character
     * @param line string to extract the line information
     * @param delim delimitation character
     * @return a vector with the line code and description
     */
    std::vector<std::string> readLine(std::string line, char delim);
    /**
     * Reads a stops from the string passed in the argument, splitting it using the delimitation character
     * @param line string to extract the stop information
     * @param delim delimitation character
     * @return vector with all the stop code information
     */
    std::vector<std::string> readStop(std::string line, char delim);

    /**
     * Reads a line path correspondent to the line and direction passed in the argument
     * @param line code string of the bus line
     * @param direction 0 or 1 direction of the bus line
     * @return vector with the stops that the line passes, ordered in the way the the bus goes
     */
    std::vector<std::string> readLinePath(std::string line, std::string direction);
    /**
     * Gets the line description of the matching code argument using the lines map
     * @param code string code of the bus line
     * @return description string of the bus line
     */
    std::string getLine(std::string code);
    /**
     * Gets the stop code of the matching integer identifier argument of the node using the stops map
     * @param node integer identifier of the node in the graph
     * @return stop code string
     */
    std::string getStop(int node);
    /**
     * Gets the integer identifier of the matching stop code argument using nodes map
     * @param stop string code of the stop
     * @return integer identifier of the correspondent node
     */
    int getNode(std::string stop);
};

#endif //GRAPHS_AED_DATA_H
