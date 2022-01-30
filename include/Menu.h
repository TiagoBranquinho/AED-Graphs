//
// Created by Tiago Branquinho on 26/01/2022.
//

#ifndef GRAPHS_AED_MENU_H
#define GRAPHS_AED_MENU_H

#include "App.h"


class Menu {
protected:
    App &app;
public:
    explicit Menu(App &app);
    virtual ~Menu();
    virtual void display()=0;
    virtual Menu *nextMenu()=0;
    int readInt();
    std::string readStr();
    double readCoordinate();
    void waitForKey();
    Menu *invalidInput();
};

class MainMenu: public Menu{
public:
    explicit MainMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

class TravelMenu: public Menu{
public:
    explicit TravelMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

class InformationMenu: public Menu{
public:
    explicit InformationMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};
class OptionsMenu: public Menu{
public:
    explicit OptionsMenu(App &app);
    void display() override;
    Menu *nextMenu() override;
};

class DistanceMenu: public Menu{
private:
    int src;
    int dest;
public:
    explicit DistanceMenu(App &app, int src, int dest);
    void display() override;
    Menu *nextMenu() override;
};

class PathMenu: public Menu{
private:
    int src;
    int dest;
public:
    explicit PathMenu(App &app, int src, int dest);
    void display() override;
    Menu *nextMenu() override;
};




#endif //GRAPHS_AED_MENU_H
