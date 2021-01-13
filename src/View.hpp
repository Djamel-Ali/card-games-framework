#ifndef CARD_GAMES_FRAMEWORK_VIEW_HPP
#define CARD_GAMES_FRAMEWORK_VIEW_HPP

#include "Model/Player.hpp"
#include "Model/Game.hpp"


class View {

protected:
    Game * game;

public:
    View();
    ~View();

    static int printWelcomeInterface();
    static void printPlayer(const Player &player);
    static void printWinner(const Player &player);
    void update();

    int play(int max, Player * player);
    void setGame(Game * _game);
    static int rejouer();
    static void aurevoir();

    static void cantPlay();
};


#endif //CARD_GAMES_FRAMEWORK_VIEW_HPP
