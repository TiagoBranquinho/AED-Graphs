//
// Created by Tiago Branquinho on 26/01/2022.
//

#ifndef GRAPHS_AED_APPSTARTER_H
#define GRAPHS_AED_APPSTARTER_H


#include "App.h"
#include "Menu.h"

class AppStarter {
    App app;
    stack<Menu*> menuStack;
public:
    AppStarter();
    void start();
};


#endif //GRAPHS_AED_APPSTARTER_H
