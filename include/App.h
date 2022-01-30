#ifndef GRAPHS_AED_APP_H
#define GRAPHS_AED_APP_H

#include "Data.h"
#include "GraphGN.h"
#include "structs.h"
#include "GraphLines.h"

#include <fstream>

class App {
public:
    enum MODE {DAY, NIGHT};
    map<MODE, GraphGN> graphGN;
    map<MODE, GraphLines> graphLN;
    MODE CURRENT_MODE = DAY;

private:
    int maxWalkDist = 0;
    Data data;
    GraphGN dayGraph;
    GraphGN nightGraph;
    GraphLines dayGraphLines;
    GraphLines nightGraphLines;

public:
    /**
     * App class default constructor
     */
    App();
    /**
     * Calls data load methods
     */
    void loadData();
    /**
     * Gets a reference to the data object of this class
     * @return Data object passed by reference
     */
    Data &getData();
    /**
     * Gets a reference to the current GraphGN object in use depending on the mode (day or night)
     * This GraphGN is used in all algorithms except in those where is calculated the best path with less line changes
     * @return GraphGN object passed by reference
     */
    GraphGN &getGraphGN();
    /**
     * Gets a reference to the current GraphLines object in use depending on the mode (day or night)
     * This GraphLines is used in the algorithms where is calculated the best path with less line changes
     * @return GraphLines object passed by reference
     */
    GraphLines &getGraphLN();
    /**
     * Gets the current maximum walk distance between two stops
     * @return maximum walk distance, which is measured in metres
     */
    int getMaxWalkDist();
    /**
     * Sets a new maximum walk distance between two stops and reloads all graphs
     * @param dist maximum walk distance in metres
     */
    void setMaxWalkDist(int dist);
    /**
     * Gets the current Mode of the App, day mode or night mode
     * @return enumerator the matches the current Mode
     */
    MODE currentMode() const;
    /**
     * Sets the current App mode with a new mode depending on the Mode argument
     * @param mode enumerator the matches the new Mode
     */
    void setCurrentMode(MODE mode);
    /**
     * Gets the current Data connector map, depending on the current App mode
     * @return a reference to the current Data connector
     */
    std::map<int,int> &getConnector();
    /**
     * Gets the current Data inverter map, depending on the current App mode
     * @return a reference to the current Data inverter
     */
    std::map<int,std::vector<int>> &getInverter();
    /**
     * Resets all graph's data
     */
    void resetGraphs();

    /**
     * Creates all graphs data and structure
     */
    void createGraphs();
    /**
     * Creates the paths of the bus lines in the graph passed by the GraphGN argument
     * @param graph GraphGN object passed by reference
     * @param line bus line to create the path in the graph
     * @param path a list of stop codes where the line passes
     */
    void createLinePath(GraphGN &graph, std::string line, std::vector<std::string> path);
    /**
     * Creates the paths of the bus lines in the graph passed by the GraphLines argument
     * Also connects all nodes where there is a walk path available, depending on the maximum walk distance
     * @param graph GraphLines object passed by reference
     * @param connector Data connector map passed by reference, that will used in the path line creation
     * @param inverter Data inverter map passed by reference, that will used in the path line creation
     * @param line bus line to create the path in the graph
     * @param path a list of stops codes where the line passes
     */
    void createLinePath(GraphLines &graph, map<int, int> &connector, map<int, vector<int>> &inverter, std::string line, std::vector<std::string> path);
    /**
     * Created all the Walk paths between GraphGN nodes, depending on the maximum walk distance
     */
    void createWalkPaths();

    /**
     * Adds walk paths to a node passed in the argument, depending on the direction of the walk paths
     * @param node integer node identifier in the graph
     * @param direction 0 if the node is an origin node, so walk paths go from inside out or 1 if the node is a destination node, then the walk paths go from outside to inside of the node
     */
    void addWalkPathsToNode(int node, int direction);
    /**
     * Adds a new location node with the coordinates passed in the local argument
     * @param local a pair with the first element is latitude and the second is longitude
     * @param name string name of the location
     * @param direction 0 if the node is an origin location or 1 if the node is a destination node
     * @return index identifier of the node that was added to the graphs
     */
    int addLocalNode(pair<double, double> local, string name, int direction);
    /**
     * Removed the node passed in the argument
     * @param node integer node identifier in the graphs
     */
    void removeLocalNode(int node);

    /**
     * Method that process a path list with the nodes and lines through which the passenger travels
     * @param path a list of pairs where the first element is the node identifier and the second is the line through which node connects to the node in next pair of the list
     * @param graphLN true is processing a path in the GraphGN object or the GraphLines object, this last one exclusive for line changes algorithms
     */
    void viewPath(vector<pair<int, string>> path, bool graphLN);

    /**
     * Calculates the distance between two stops passed in the arguments
     * @param src integer identifier of the source stop in the GraphGN
     * @param dest integer identifier of the destiny stop in the GraphGN
     * @return integer distance in metres
     */
    int distance(int src, int dest);
    /**
     * Calculates the real distance between two locations passed by their latitude and longitude coordinates
     * @param lat1 latitude value of the first location
     * @param lon1 longitude value of the first location
     * @param lat2 latitude value of the second location
     * @param lon2 longitude value of the second location
     * @return integer distance between the locals in meters
     */
    static int haversine(double lat1, double lon1, double lat2, double lon2);
};

#endif //GRAPHS_AED_APP_H
