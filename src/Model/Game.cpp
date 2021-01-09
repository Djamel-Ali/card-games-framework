#include <iostream>
#include "Game.hpp"

Game::Game(Deck *_deck, int player) :joueurs{}{
    deck = _deck;
    actualPlaying = 0;
    std::cout << "Construction of Game" << std::endl;
}

void Game::initGame() {
    createCards();
    deck->shuffleCards();
}

ostream &operator<<(ostream &out, Game &game) {
    out << " -------------------------------------------------------------------- " << endl;

    game.print(out);

    out << " -------------------------------------------------------------------- " << endl;
    return out;
}

Player* Game::getActualPlaying() const {
    return joueurs.at(actualPlaying);
}

Player *Game::getPlayer(int iPlayer) const {
    return joueurs[iPlayer];
}

void Game::startGame() {
    initGame();
    distribution();
}

void Game::createCards() {
    cout  << "Create cards Game" << endl;
}

