#include "../include/Menu.h"

#include <sstream>

using namespace std;

Menu::~Menu() = default;

Menu::Menu(App &app): app(app) {}

int Menu::readInt() {
    int opt;
    while (true){
        stringstream ss;
        ss << readStr(); ss >> opt;
        if(!ss.fail() && ss.eof() && opt>=0) break;
        cout << "Invalid input. Try a valid integer..." << endl;
    }
    cout << endl;
    return opt;
}

void Menu::waitForKey() {
    string str;
    cout << endl << "Press enter to continue..." << endl;
    getline(cin, str);
}

std::string Menu::readStr() {
    string str,ret;
    cout << ": ";
    getline(cin, str);
    for(char &c : str){
        ret += toupper(c);
    }
    return ret;
}

Menu *Menu::invalidInput() {
    cout << "Invalid input option!" << endl;
    return this;
}

double Menu::readCoordinate() {
    double coord;
    while (true){
        stringstream ss;
        ss << readStr(); ss >> coord;
        if(!ss.fail() && ss.eof()) break;
        cout << "Invalid input. Try a valid integer..." << endl;
    }
    cout << coord << endl;
    cout << endl;
    return coord;
}

MainMenu::MainMenu(App &app): Menu(app){}

void MainMenu::display(){
    cout << endl;
    cout << "Main Menu:" << endl;
    cout << "1 - Travel Menu" << endl;
    cout << "2 - Information Menu" << endl;
    cout << "3 - Options Menu" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *MainMenu::nextMenu() {
    switch (readInt()) {
        case 1: return new TravelMenu(app);
        case 2: return new InformationMenu(app);
        case 3: return new OptionsMenu(app);
        case 0: return nullptr;
        default: return invalidInput();
    }
}

OptionsMenu::OptionsMenu(App &app) : Menu(app) {

}

void OptionsMenu::display() {
    cout << endl;
    cout << "Options Menu:" << endl;
    cout << "1 - Change max walking distance" << " (current: " << app.getMaxWalkDist() << "m)" << endl;
    cout << "2 - Change between day/night only mode" << " (current: " << (app.currentMode() == 0 ? "day" : "night") << ")" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *OptionsMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            cout << "Current max walking distance is " << to_string(app.getMaxWalkDist()) << endl;
            cout << "Please insert the new value: ";
            int dist = readInt();
            cout << "Loading graphs..." << endl;
            app.setMaxWalkDist(dist);
            cout << "Loading complete." << endl;
            waitForKey();
            return this;
        }
        case 2:{
            cout << "Current mode is " << (app.currentMode() == 0 ? "day" : "night") << endl;
            cout << "Please insert: " << endl << "0 - day mode" << endl <<"1 - night mode" << endl;
            int mode = readInt();
            app.setCurrentMode(static_cast<App::MODE>(mode));
            cout << "Current mode is " << (app.currentMode() == 0 ? "day" : "night") << endl;
            waitForKey();
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

TravelMenu::TravelMenu(App &app) : Menu(app) {

}

void TravelMenu::display() {
    cout << endl;
    cout << "Travel Menu:" << endl;
    cout << "1 - View Path stop-to-stop" << endl;
    cout << "2 - View Path location-to-location" << endl;
    cout << "3 - View Path location-to-stop" << endl;
    cout << "4 - View Path stop-to-location" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *TravelMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            cout << "Origin stop code: ";
            string stop1 = readStr();
            if(app.getData().nodes.count(stop1) == 0){
                cout << "Origin stop doesn't exist";
                return this;
            }
            cout << "Destination stop code: ";
            string stop2 = readStr();
            if(app.getData().nodes.count(stop2) == 0){
                cout << "Destination stop doesn't exist";
                return this;
            }
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            return new PathMenu(app,src,dest);
        }
        case 2: {
            cout << "Origin latitude: ";
            double srcLat = readCoordinate();
            cout << "Origin longitude: ";
            double srcLong = readCoordinate();
            cout << "Destination latitude: ";
            double destLat = readCoordinate();
            cout << "Destination longitude: ";
            double destLong = readCoordinate();
            int src = app.addLocalNode({srcLat, srcLong}, "Origin Local", 0);
            int dest = app.addLocalNode({destLat, destLong}, "Destination Local", 1);
            return new PathMenu(app,src,dest);
        }
        case 3: {
            cout << "Origin latitude: ";
            double srcLat = readCoordinate();
            cout << "Origin longitude: ";
            double srcLong = readCoordinate();
            cout << "Destination stop code: ";
            string stop2 = readStr();
            if(app.getData().nodes.count(stop2) == 0){
                cout << "Destination stop doesn't exist";
                return this;
            }
            int src = app.addLocalNode({srcLat, srcLong}, "Origin Local", 0);
            int dest = app.getData().getNode(stop2);
            return new PathMenu(app,src,dest);
        }
        case 4: {
            cout << "Origin stop code: ";
            string stop1 = readStr();
            if(app.getData().nodes.count(stop1) == 0){
                cout << "Origin stop doesn't exist";
                return this;
            }
            cout << "Destination latitude: ";
            double destLat = readCoordinate();
            cout << "Destination longitude: ";
            double destLong = readCoordinate();
            int src = app.getData().getNode(stop1);
            int dest = app.addLocalNode({destLat, destLong}, "Destination Local", 1);
            return new PathMenu(app,src,dest);
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

InformationMenu::InformationMenu(App &app) : Menu(app) {

}

void InformationMenu::display() {
    cout << endl;
    cout << "Information Menu:" << endl;
    cout << "1 - Distance between two stops" << endl;
    cout << "2 - Lines between two stops" << endl;
    cout << "3 - Zones between two stops" << endl;
    cout << "4 - Stations between two stops" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *InformationMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            cout << "Stop 1 code: ";
            string stop1 = readStr();
            if(app.getData().nodes.count(stop1) == 0){
                cout << "Stop 1 doesn't exist";
                return new OptionsMenu(app);
            }
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            if(app.getData().nodes.count(stop2) == 0){
                cout << "Stop 2 doesn't exist";
                return new OptionsMenu(app);
            }
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            return new DistanceMenu(app, src, dest);
        }
        case 2: {
            cout << "Stop 1 code: ";
            string stop1 = readStr();
            if(app.getData().nodes.count(stop1) == 0){
                cout << "Stop 1 doesn't exist";
                return new OptionsMenu(app);
            }
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            if(app.getData().nodes.count(stop2) == 0){
                cout << "Stop 2 doesn't exist";
                return new OptionsMenu(app);
            }
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            vector<int> srcLN = app.getInverter()[src];
            for (const auto& edge : app.getGraphGN().getNodes()[src].adj)
                srcLN.insert(srcLN.end(), app.getInverter()[edge.dest].begin(), app.getInverter()[edge.dest].end());
            vector<int> destLN = app.getInverter()[dest];
            for (const auto& edge : app.getGraphGN().getNodes()[dest].adj)
                destLN.insert(destLN.end(), app.getInverter()[edge.dest].begin(), app.getInverter()[edge.dest].end());
            int numLines = app.getGraphLN().dijkstraDistanceLN(srcLN,destLN);
            if (numLines < 0){
                cout << "No path available" << endl;
                return this;
            }
            string word = "lines";
            cout << "Stations " << app.getData().stopsVector[src].name << " and " << app.getData().stopsVector[dest].name << " are ";
            if(numLines == 0)
                cout << "in the same line" << endl;
            else{
                if(numLines == 1)
                    word = word.substr(0,word.size()-1);
                cout << to_string(numLines) << " " << word << " away from each other" << endl;
            }
            waitForKey();
            return this;
        }
        case 3: {
            cout << "Stop 1 code: ";
            string stop1 = readStr();
            if(app.getData().nodes.count(stop1) == 0){
                cout << "Stop 1 doesn't exist";
                return new OptionsMenu(app);
            }
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            if(app.getData().nodes.count(stop2) == 0){
                cout << "Stop 2 doesn't exist";
                return new OptionsMenu(app);
            }
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            int numZones = app.getGraphGN().dijkstraDistanceZN(src,dest) - 1;
            if (numZones < 0){
                cout << "No path available" << endl;
                return this;
            }
            string word = "lines";
            cout << "Stations " << app.getData().stopsVector[src].name << " and " << app.getData().stopsVector[dest].name << " are ";
            if(numZones == 0)
                cout << "in the same line" << endl;
            else{
                if(numZones == 1)
                    word = word.substr(0,word.size()-1);
                cout << to_string(numZones) << " " << word << " away from each other" << endl;
            }
            waitForKey();
            return this;
        }
        case 4: {
            cout << "Stop 1 code: ";
            string stop1 = readStr();
            if(app.getData().nodes.count(stop1) == 0){
                cout << "Stop 1 doesn't exist";
                return new OptionsMenu(app);
            }
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            if(app.getData().nodes.count(stop2) == 0){
                cout << "Stop 2 doesn't exist";
                return new OptionsMenu(app);
            }
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            int numStops = abs((int)app.getGraphGN().bfsPathST(src,dest).size() - 1);
            if (numStops < 0){
                cout << "No path available" << endl;
                return this;
            }
            string word = "stops";
            cout << "Stations " << app.getData().stopsVector[src].name << " and " << app.getData().stopsVector[dest].name << " are ";
            if(numStops == 0)
                cout << "are the same" << endl;
            else{
                if(numStops == 1)
                    word = word.substr(0,word.size()-1);
                cout << to_string(numStops) << " " << word << " away from each other" << endl;
            }
            waitForKey();
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

DistanceMenu::DistanceMenu(App &app, int src, int dest) : Menu(app), src(src), dest(dest) {

}

void DistanceMenu::display() {
    cout << endl;
    cout << "Distance Menu:" << endl;
    cout << "1 - Geographical distance" << endl;
    cout << "2 - Travelling distance" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *DistanceMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            cout << app.getData().stopsVector[src].name << " and " << app.getData().stopsVector[dest].name << " stations are " << to_string(app.distance(src,dest)) << "m away from each other" << endl;
            waitForKey();
            return this;
        }
        case 2: {
            int dist = app.getGraphGN().dijkstraDistanceDS(src,dest);
            if (dist < 0){
                cout << "No path available" << endl;
                return this;
            }
            cout << app.getData().stopsVector[src].name << " and " << app.getData().stopsVector[dest].name << " stations are, travelling by public transports, " << dist << "m away from each other " << endl;
            waitForKey();
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}

PathMenu::PathMenu(App &app, int src, int dest) : Menu(app), src(src), dest(dest) {

}

void PathMenu::display() {
    cout << endl;
    cout << "Path Menu:" << endl;
    cout << "1 - Preference: cheaper (lowest zone changes)" << endl;
    cout << "2 - Preference: lowest distance" << endl;
    cout << "3 - Preference: lowest line changes" << endl;
    cout << "4 - Preference: less number of stops" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *PathMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            app.viewPath(app.getGraphGN().dijkstraPathZN(src, dest), false);
            waitForKey();
            return this;
        }
        case 2: {
            app.viewPath(app.getGraphGN().dijkstraPathDS(src, dest), false);
            waitForKey();
            return this;
        }
        case 3: {
            vector<int> srcLN = app.getInverter()[src];
            for (const auto& edge : app.getGraphGN().getNodes()[src].adj)
                srcLN.insert(srcLN.end(), app.getInverter()[edge.dest].begin(), app.getInverter()[edge.dest].end());
            vector<int> destLN = app.getInverter()[dest];
            for (const auto& edge : app.getGraphGN().getNodes()[dest].adj)
                destLN.insert(destLN.end(), app.getInverter()[edge.dest].begin(), app.getInverter()[edge.dest].end());

            auto path = app.getGraphLN().dijkstraPathLN(srcLN, destLN);
            if (!path.empty()){
                if (path[0].second != app.getData().getStop(src)) path.insert(path.begin(), {app.getInverter()[src][0], "WALK"});
                if (path.back().second != app.getData().getStop(dest)){
                    path.back().second = "WALK";
                    path.insert(path.end(), {app.getInverter()[dest][0], ""});
                }
            }
            app.viewPath(path, true);
            waitForKey();
            return this;
        }
        case 4: {
            app.viewPath(app.getGraphGN().bfsPathST(src, dest), false);
            waitForKey();
            return this;
        }
        case 0:{
            if (app.getGraphGN().getNodes()[dest].name=="Destination Local") app.removeLocalNode(dest);
            if (app.getGraphGN().getNodes()[src].name=="Origin Local") app.removeLocalNode(src);
            return nullptr;
        }
        default: return invalidInput();
    }
}