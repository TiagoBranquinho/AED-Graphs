#include <sstream>
#include "../include/Menu.h"

using namespace std;

Menu::~Menu() = default;

Menu::Menu(App &app): app(app) {}

int Menu::readInt() {
    int opt; string optstr;
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
    cout << "1 - Change max walking distance" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *OptionsMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            cout << "Stop 1 code: ";
            string stop1 = readStr();
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            return new PathMenu(app,src,dest);
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
    cout << "1 - View Path between two stops" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *TravelMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            cout << "Stop 1 code: ";
            string stop1 = readStr();
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
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
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            return new DistanceMenu(app, src, dest);
        }
        case 2: {
            cout << "Stop 1 code: ";
            string stop1 = readStr();
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            int numLines = app.getGraph().dijkstraDistanceLN(src,dest) - 1;
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
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            int numZones = app.getGraph().dijkstraDistanceZN(src,dest) - 1;
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
            cout << "Stop 2 code: ";
            string stop2 = readStr();
            int src = app.getData().getNode(stop1);
            int dest = app.getData().getNode(stop2);
            int numStops = abs((int)app.getGraph().bfsPathST(src,dest).size() - 1);
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
            cout << app.getData().stopsVector[src].name << " and " << app.getData().stopsVector[dest].name << " stations are " << to_string(app.distance(src,dest)) << "km away from each other" << endl;
            waitForKey();
            return this;
        }
        case 2: {
            cout << app.getData().stopsVector[src].name << " and " << app.getData().stopsVector[dest].name << " stations are, travelling by public transports, " << to_string(app.getGraph().dijkstraDistanceDS(src,dest)) << "km away from each other " << endl;
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
    cout << "1 - Preference: cheaper" << endl;
    cout << "2 - Preference: lowest distance" << endl;
    cout << "3 - Preference: lowest line changes" << endl;
    cout << "0 - Exit" << endl;
    cout << endl;
}

Menu *PathMenu::nextMenu() {
    switch (readInt()) {
        case 1: {
            app.viewPath(app.getGraph().dijkstraPathZN(src,dest));
            waitForKey();
            return this;
        }
        case 2: {
            app.viewPath(app.getGraph().dijkstraPathDS(src,dest));
            waitForKey();
            return this;
        }
        case 3: {
            app.viewPath(app.getGraph().dijkstraPathLN(src,dest));
            waitForKey();
            return this;
        }
        case 0: return nullptr;
        default: return invalidInput();
    }
}