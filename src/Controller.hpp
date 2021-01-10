#ifndef CARD_GAMES_FRAMEWORK_CONTROLLER_HPP
#define CARD_GAMES_FRAMEWORK_CONTROLLER_HPP

#include "View.hpp"
#include "Model/Game.hpp"
#include "Model/Jeu/Bataille.hpp"
#include "Model/Jeu/HuitAmericain.hpp"
#include "Model/Jeu/UNO.hpp"
#include "Model/Jeu/Belote.hpp"
#include "Model/Jeu/Tarot.hpp"

class Controller {

protected:
    Game *game;
    View *view;

    friend class View;

public:
    Controller(View *vue, int jeu);
    ~Controller();

    void startGame();
    void updateView();
};


#endif //CARD_GAMES_FRAMEWORK_CONTROLLER_HPP
