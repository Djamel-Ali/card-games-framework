#include "Controller.hpp"
#include "View.hpp"

Controller::Controller(View * vue) :view(vue){

}

Game *Controller::setGame(int jeu) {
    vector<Card *> cards;
    Deck deck{cards};

    switch (jeu) {
        case 1:
            return new Bataille(deck);
        case 2:
            return new HuitAmericain(deck);
        case 3:
            return new UNO(deck);
        case 4:
            return new Belote(deck);
        default:
            return new Belote(deck);
    }

}

void Controller::updateView() {
    view -> update();
}

void Controller::startGame() {
    game -> startGame();
    updateView();
    while (!game -> isWinner()){
        game -> playRound(view->play((int)game->getActualPlaying()->getHand().size() -1, game->getActualPlaying()));
        updateView();
        game -> nextPlayer();
    }

}

void Controller::setVue(View *vue) {
     view = vue;
}
