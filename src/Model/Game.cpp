#include <iostream>
#include "Game.hpp"

Game::Game(Deck *_deck) :joueurs{}{
    deck = _deck;
    actualPlaying = 0;
    std::cout << "Construction of Game" << std::endl;
}

/**
* Initiation de la Partie (Création des cartes + mélanger)
 */
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

/**
* Retourne l'indice du joueur actuel
 */

Player* Game::getActualPlaying() const {
    return joueurs.at(actualPlaying);
}

/**
* Retourn un joueur selon son indice
 */
Player *Game::getPlayer(int iPlayer) const {
    return joueurs[iPlayer];
}

/**
* Initiation de la partie et distribution des cartes
 */

void Game::startGame() {
    initGame();
    distribution();
}

void Game::createCards() {
    cout  << "Create cards Game" << endl;
}

Game::~Game() {
    delete deck;
    for(Player *player : joueurs){
        delete player;
    }
}

