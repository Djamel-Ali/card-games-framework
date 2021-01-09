#ifndef CARD_GAMES_FRAMEWORK_VIEW_HPP
#define CARD_GAMES_FRAMEWORK_VIEW_HPP

#include <iostream>
#include "Model/Player.hpp"
#include "Model/Game.hpp"

using namespace std;

class View {

public:
    View();

    int printWelcomeInterface();
    void printPlayer(const Player &player);
    void printHand(const Player &player);
    void update(Game *game);

    int play(int max, Player * player);
    void start();


};


#endif //CARD_GAMES_FRAMEWORK_VIEW_HPP
