#include <iostream>
#include <algorithm>
#include "Deck.hpp"
#include <vector>
#include <random>
#include <chrono>

// Ctor
Deck::Deck() {
    std::cout << "construction of Deck" << std::endl;
}

// Dtor
Deck::~Deck(){
    for(Card* temp : deck_of_cards){
        delete temp;
    }
}

// Getters :

const vector<Card*> &Deck::getDeckOfCards() const {
    return deck_of_cards;
}

// Other methods :

// Stack a new card in the deck of cards.
void Deck::addCard(Card *pCard) {
    deck_of_cards.push_back(pCard);
}

Card *Deck::getCard() {
    Card* temp = deck_of_cards.front();
    deck_of_cards.erase(deck_of_cards.begin());

    return temp;
}

void Deck::shuffleCards() {
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();

    shuffle(deck_of_cards.begin(), deck_of_cards.end(), std::default_random_engine(seed));
}


void Deck::distributeCards(int nbCards, const vector<Player *> &players) {
    for(Player* player: players){
        for(int i = 0; i < nbCards; i++){
            player->addCard(this->getCard());
        }
    }

    cout << "Cartes distribuées aux players" << endl;
}



