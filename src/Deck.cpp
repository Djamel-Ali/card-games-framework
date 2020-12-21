#include <iostream>
#include <random>
#include <algorithm>
#include "Deck.hpp"

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
    std::random_device randomDevice;
    auto engine = std::default_random_engine {randomDevice() };
    std::shuffle(std::begin(deck_of_cards), std::end(deck_of_cards), engine);
}
