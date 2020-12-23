#include <iostream>
#include <algorithm>
#include "Deck.hpp"
#include <cstdlib>
#include <random>
// Ctor
Deck::Deck(const vector<Card*> &_deckOfCards) : deck_of_cards(_deckOfCards) {
    std::cout << "construction of Deck" << std::endl;
}

// Dtor
Deck::~Deck() = default;

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
    shuffle(deck_of_cards.begin(), deck_of_cards.end(), std::mt19937(std::random_device()()));
}


void Deck::distributeCards(int nbCards, const vector<Player *> &players) {
    for(Player* player: players){
        for(int i = 0; i < nbCards; i++){
            player->addCard(this->getCard());
        }
    }
}



