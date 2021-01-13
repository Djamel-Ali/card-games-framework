#include <iostream>
#include <random>
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
        cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t\t Bien joué "
        << joueurs.at(actualPlaying)->getName() << " (la carte est jouable)" << endl;
        tapis.insert(tapis.begin(), temp);
        nextPlayer();
    }else{
        joueurs[actualPlaying]->addCard(temp);
        cout << "la carte n'est pas jouable " << endl;
        system("read -p 'Appuyez sur Entrer pour continuer...' var");
    }
}

int Game::playAuto() {
    vector<int> index;
    vector<Card *> hand = joueurs[actualPlaying]->getHand();
    for(int i = 0; i < (int)hand.size(); i++){
        if(cardPlayable(hand.at(i))){
            index.push_back(i);
        }
    }
    int randIndex = getRandomSignedInt(0, (int)index.size()-1);
    system("read -p 'Appuyez sur Entrer pour continuer...' var");
    return index[randIndex];
}

int Game::getRandomSignedInt(const int minValue, const int maxValue) {

    // Non-deterministic 32-bit seed
    std::random_device rd;
    std::mt19937 mt(rd());

    // distribution: [minValue, maxValue] ; Note : [inclusive, inclusive]
    std::uniform_int_distribution<int> distribution(minValue, maxValue);
    return distribution(mt);
}