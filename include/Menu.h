#ifndef GRAPHS_AED_MENU_H
#define GRAPHS_AED_MENU_H

#include "App.h"


class Menu {
protected:
    App &app;
public:
    /**
     * Class constructor with an application object
     * @param app application object passed by reference
     */
    explicit Menu(App &app);
    /**
     * Class destructor to clear the object in memory
     */
    virtual ~Menu();
    /**
     * Displays the menu in the terminal
     */
    virtual void display()=0;
    /**
     * Gets a menu pointer to the next menu after this one
     * @return menu pointer
     */
    virtual Menu *nextMenu()=0;
    /**
     * Reads an integer number input from the terminal
     * @return integer number read
     */
    int readInt();
    /**
     * Reads a string input from the terminal
     * @return string read
     */
    std::string readStr();
    /**
     * Reads a double input from the terminal
     * @return double number read
     */
    double readCoordinate();
    /**
    * Waits for enter key to be pressed
    */
    void waitForKey();
    /**
     * If there was an invalid input prints a message and returns a pointer the a current menu
     * @return menu pointer
     */
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
