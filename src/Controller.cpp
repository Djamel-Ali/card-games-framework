#include "Controller.hpp"


Controller::Controller(View * vue, int jeu) :view(vue){
    Deck * deck = new Deck();
    int player = 0;
    switch (jeu) {
        case 1:
            game = new Bataille(deck, 0);
        case 2:
            game = new HuitAmericain(deck, 0);
        case 3:
            game = new UNO(deck, 0);
        case 4:
            game = new Belote(deck, 0);
        case 5:
            game = new Belote(deck, 0);
        default:
            game = new Bataille(deck, player);

    }

}

void Controller::updateView() {
    view -> update(game);
}

void Controller::startGame() {
    game -> startGame();
    updateView();
    while (!game -> isWinner()){
        game -> playRound(view->play((int)game->getActualPlaying()->getHand().size() -1, game->getActualPlaying()));
        updateView();
    }

    view ->printPlayer(*game->getPlayer(game->getWinner()));
}

