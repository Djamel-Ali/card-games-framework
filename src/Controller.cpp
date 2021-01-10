#include "Controller.hpp"


Controller::Controller(View * vue, int jeu) :view(vue){
    Deck * deck = new Deck();
    int player = 0;
    switch (jeu) {
        case 1:
            game = new Bataille(deck, 0);
            break;
        case 2:
            game = new HuitAmericain(deck, 0);
            break;
        case 3:
            game = new UNO(deck, 0);
            break;
        case 4:
            game = new Belote(deck, 0);
            break;
        case 5:
            game = new Belote(deck, 0);
            break;
        default:
            game = new Bataille(deck, player);
            break;
    }
    view ->setGame(game);
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

