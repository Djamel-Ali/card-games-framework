#include <iostream>
#include "HuitAmericain.hpp"

using namespace std;
HuitAmericain::HuitAmericain(const Deck &deck) : Game(deck), sensInverse{false} {
    cout << "\nConstruct HuitAmericain\n" << endl;
}

HuitAmericain::~HuitAmericain() = default;


/// Remarque : pour 8 americain on a besoin d'un jeu de 54 cartes et non pas de 52 cartes comme c'est
/// écrit dans le site https://www.regles-de-jeux.com/regle-du-8-americain/ (car on utilise ici les 3 joker)
void HuitAmericain::initGame() {
    COLOR symbols[] = {TREFLE, COEUR, CARREAU, PIQUE, NONE};

    // cards  3 - 7 (Leur propre valeur numérale)
    for (int numero = 3; numero <= 7; numero++){
        for (int symbol = 0; symbol < 4; symbol++){
            deck.addCard(new ColoredCard(to_string(numero), numero, numero, symbols[symbol]));
        }
    }
    // cards  "9" (leur propre valeur numérale)
    for (int symbol = 0; symbol < 4; symbol++){
        deck.addCard(new ColoredCard(to_string(9), 9,9,symbols[symbol]));
    }

    // cards  "Dame" and "Roi" (value 10 points)
    for (int symbol = 0; symbol < 4; symbol++){
        deck.addCard(new ColoredCard("DAME", 10,10,symbols[symbol]));
        deck.addCard(new ColoredCard("ROI", 11,10,symbols[symbol]));
    }

    // cards  Valet, AS, 2 (value 20 points )
    for (int symbol = 0; symbol < 4; symbol++){
        deck.addCard(new ColoredCard("VALET", 12,20, symbols[symbol]));
        deck.addCard(new ColoredCard("AS", 13,20, symbols[symbol]));
        deck.addCard(new ColoredCard("2", 2,20, symbols[symbol]));
    }

    // cards "8" and "Joker" : (value 50 points )
    // (4 cartes de 8 et 2 cartes de jocker avec NONE comme symbol)
    for (int symbol = 0; symbol < 4; symbol++)
        deck.addCard(new ColoredCard(to_string(8),  8,50, symbols[symbol]));
    deck.addCard(new ColoredCard("JOKER", 14, 50, symbols[4]));

    // Shuffle the deck of cards that has just been created
    deck.shuffleCards();

}

void HuitAmericain::distributeCards() {
    for(Player* player : joueurs){
        for(int i = 0; i < 8; i++){
            player->addCard(deck.getCard());
        }
    }
}

void HuitAmericain::startGame() {
    initGame();
}

//todo: modifications a faire pour le controller !!
void HuitAmericain::playRound(int indexCardToPlay) {
    if(isWinner()){
        getWinner();
        return;
    }

    Card* temp = joueurs[actualPlaying]->playCard(indexCardToPlay);
    if(cardPlayable(temp)){
        deck.addCard(cardOnTop);
        cardOnTop = temp;
        getIndexOfParseCard();

        nextPlayer();
    }

    while(!isWinner()){
        playRound();
    }
}

int HuitAmericain::getIndexOfParseCard() {
    switch (cardOnTop->getId()) {
        case 1:
            // "AS" (Les As font changer le sens du jeu)
            reversed();
            break;
        case 2:
            // "2" (Les 2 font font piocher + 2 cartes au joueur suivant)
            nextPlayer();
            plusTwo();
            break;
        case 8:
            // "8" (Les 8 permettent de changer de couleur à n’importe quel moment)
            return 1;
        case 12:
            // "VALET" (Les Valets font sauter le tour du joueur suivant)
            nextPlayer();
            break;
        case 14:
            // "JOKER" (Les Jokers font piocher + 4 cartes au joueur suivant)
            nextPlayer();
            plusFour();
            break;
    }
    return 0;
}

bool HuitAmericain::isWinner() {
    for(Player* pPlayer : joueurs){
        if(pPlayer->handEmpty()){
            return true;
        }
    }
    return false;
}

int HuitAmericain::getWinner() {
    for(int i = 0; i < joueurs.size(); i ++){
        if (joueurs.at(i)->handEmpty()){
            return i;
        }
    }
    return -1;
}

void HuitAmericain::plusTwo() {
    for(int i = 0; i < 2; i ++){
        joueurs[actualPlaying]->addCard(deck.getCard());
    }
}

void HuitAmericain::plusFour() {
    for(int i = 0; i < 4; i ++){
        joueurs[actualPlaying]->addCard(deck.getCard());
    }
}

void HuitAmericain::reversed() {
    sensInverse = !sensInverse;
}

void HuitAmericain::nextPlayer() {
    actualPlaying = (sensInverse) ? (actualPlaying -1) : (actualPlaying +1);

    if(actualPlaying < 0) actualPlaying = int(joueurs.size()) -1;
    if(actualPlaying >= joueurs.size()) actualPlaying = 0;
}

void HuitAmericain::changeColor() {

}

bool HuitAmericain::cardPlayable(Card *toPlay) {
    return cardOnTop == toPlay;
}
