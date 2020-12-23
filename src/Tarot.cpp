#include <iostream>
#include "Tarot.hpp"

Tarot::Tarot(const Deck &deck) : Game(deck) {
    cout << "\n\tConstruct Tarot\n" << endl;
}

void Tarot::createCards() {
    COLOR symbols[] = {TREFLE, COEUR, CARREAU, PIQUE, NONE};


    /// N.B: LES NON-ATOUTS SONT DE TYPE ColoredCard
    // [1..10] * 4 = 40 cartes basses (ou blanches) valent chacune 0,5 point (soit un total de 20 points) ;
    for (int numero = 1; numero <= 10; numero++){
        for (int symbol = 0; symbol < 4; symbol++){
            deck.addCard(new ColoredCard(to_string(numero), numero, 0.5, symbols[symbol]));
        }
    }

    /// N.B: LES ATOUTS SONT DE TYPE Card
    // [2..20] = 19 atouts du n°2 au n°20 valent chacun 0,5 point (soit un total de 9,5 points) ;
    for (int numero = 2; numero <= 20; numero++){
            deck.addCard(new Card(to_string(numero), numero, 0.5));
    }

    // les 4 Valets valent chacun 1,5 point (soit un total de 6 points) ;
    // les 4 Cavaliers valent chacun 2,5 points (soit un total de 10 points) ;
    // les 4 Dames valent chacune 3,5 points (soit un total de 14 points) ;
    // les 4 Rois valent chacun 4,5 points (soit un total de 18 points) ;
    for (int symbol = 0; symbol < 4; symbol++){
        deck.addCard(new ColoredCard("VALET", 11, 1.5,symbols[symbol]));
        deck.addCard(new ColoredCard("CAVALIER", 12, 2.5,symbols[symbol]));
        deck.addCard(new ColoredCard("DAME", 13, 3.5,symbols[symbol]));
        deck.addCard(new ColoredCard("ROI", 14, 4.5,symbols[symbol]));
    }

    // les 3 Bouts valent chacun 4,5 points (soit un total de 13,5 points) ;
    // (les cartes 1 et 21 d'atout)
    for (int numero = 1; numero <= 21; numero+=20){
        deck.addCard(new Card(to_string(numero), numero, 4.5));
    }
    // la carte 22 d'atout (l'EXCUSE)
    deck.addCard(new Card("EXCUSE", 22, 4.5));

}

void Tarot::startGame() {
    initGame();
    deck.distributeCards(18, joueurs);

    // 6 cartes restantes dans le talon (les 6 chiens)
    setChien(deck.getDeckOfCards());
}

// Getters and Setters

const vector<Card *> &Tarot::getChien() const {
    return chien;
}

void Tarot::setChien(const vector<Card *> &_chien) {
    Tarot::chien = _chien;
}

bool Tarot::isWinner() {
    return false;
}

int Tarot::getWinner() {
    return 0;
}

int Tarot::getIndexOfParseCard() {
    return 0;
}

void Tarot::playRound(int indexCardToPlay) {

}

void Tarot::nextPlayer() {

}
