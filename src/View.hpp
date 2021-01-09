#ifndef CARD_GAMES_FRAMEWORK_VIEW_HPP
#define CARD_GAMES_FRAMEWORK_VIEW_HPP

#include "Controller.hpp"
#include <iostream>


using namespace std;

class View {

protected:
    Controller *controller;

    friend class Controller;

public:
    View();

    int printWelcomeInterface();
    void printPlayer(const Player &player);
    void printHand(const Player &player);
    void update();

    int play(int max, Player * player);
    void start();
};


#endif //CARD_GAMES_FRAMEWORK_VIEW_HPP
