#ifndef CARD_GAMES_FRAMEWORK_CONTROLLER_HPP
#define CARD_GAMES_FRAMEWORK_CONTROLLER_HPP



#include "Model/Game.hpp"
#include "Model/Bataille.hpp"
#include "Model/HuitAmericain.hpp"
#include "Model/UNO.hpp"
#include "Model/Belote.hpp"

class View;

class Controller {

protected:
    Game *game;
    View *view;

    friend class View;

public:
    Controller(View *vue);
    Game * setGame(int jeu);

    void setVue(View * vue);
    void startGame();
    void updateView();
};


#endif //CARD_GAMES_FRAMEWORK_CONTROLLER_HPP
