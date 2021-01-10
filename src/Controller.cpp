#include "Controller.hpp"

Controller::Controller(View * vue, int jeu) :view(vue){
    Deck * deck = new Deck();

    switch (jeu) {
        case 1:
            game = new Bataille(deck);
            break;
        case 2:
            game = new HuitAmericain(deck);
            break;
        case 3:
            game = new UNO(deck);
            break;
        case 4:
            game = new Belote(deck);
            break;
        case 5:
            game = new Tarot(deck);
            break;
        default:
            break;
    }
    view ->setGame(game);
}

Controller::~Controller() {
    delete game;
    delete view;
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
    }

    view ->printWinner(*game->getPlayer(game->getWinner()));
}


