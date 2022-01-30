#ifndef GRAPHS_AED_APPSTARTER_H
#define GRAPHS_AED_APPSTARTER_H

#include "App.h"
#include "Menu.h"
#include <stack>

#include <stack>

class AppStarter {
    App app;
    stack<Menu*> menuStack;
public:
    /**
     * Default class constructor that pushes the main menu to the menuStack
     */
    AppStarter();
    /**
     * Starts the application loop and call the App methods to load graphs data and set the default maximum walk distance
     */
    void start();
};


#endif //GRAPHS_AED_APPSTARTER_H
