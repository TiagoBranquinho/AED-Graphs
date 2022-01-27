//
// Created by Tiago Branquinho on 26/01/2022.
//

#include "../include/AppStarter.h"

AppStarter::AppStarter() {
    menuStack.push(new MainMenu(app));
}

void AppStarter::start() {
    app.loadData();
    app.setMaxWalkDist(0);
    while (!menuStack.empty()) {
        menuStack.top()->display();
        Menu *nextMenu = menuStack.top()->nextMenu();
        if (nextMenu){
            if (nextMenu != menuStack.top()){
                menuStack.push(nextMenu);
            }
        }
        else {
            delete menuStack.top();
            menuStack.pop();
        }
    }
    //app.saveData();
}
