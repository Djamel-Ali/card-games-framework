#include <iostream>
#include "Game.hpp"

Game::Game(Deck *_deck) :joueurs{}{
    deck = _deck;
    actualPlaying = 0;
}

Game::~Game() {
    delete deck;
    for(Player *player : joueurs){
        delete player;
    }
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
* Initiation de la partie et distribution des cartes
 */

void Game::startGame() {
    initGame();
    distribution();
}

bool Game::playerCanPlay() {
    return true;
}

bool Game::cardPlayable(Card *toPlay) {
    return true;
}

void Game::playRound(int indexCardToPlay) {
    Card* temp = joueurs[actualPlaying]->playCard(indexCardToPlay);
    if(cardPlayable(temp)){
        cout << "la carte est jouable " << endl;
        tapis.insert(tapis.begin(), temp);
        cout << "carte dans tapis - tapis size == "<<tapis.size() << endl;
        nextPlayer();
    }else{
        joueurs[actualPlaying]->addCard(temp);
        cout << "la carte n'est pas jouable " << endl;
        system("pause");
    }
}
