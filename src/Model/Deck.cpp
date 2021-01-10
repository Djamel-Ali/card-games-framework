#include <iostream>
#include <algorithm>
#include "Deck.hpp"
#include <vector>
#include <random>
#include <chrono>

// Ctor

Deck::Deck() = default;

// Dtor

Deck::~Deck(){
    for(Card* temp : deck_of_cards){
        delete temp;
    }
}

// Getters :

vector<Card*> &Deck::getDeckOfCards(){
    return deck_of_cards;
}

/**
* Retourne la prémière carte du Deck et la supprime de ce dernier
 */

Card *Deck::getCard() {
    Card* temp = deck_of_cards.front();
    deck_of_cards.erase(deck_of_cards.begin());

    return temp;
}
// Other methods :

/**
* Ajouter un carte au Deck
 */

void Deck::addCard(Card *pCard) {
    deck_of_cards.push_back(pCard);
}


/**
* Mélanger les cartes
 */

void Deck::shuffleCards() {
    unsigned seed = std::chrono::system_clock::now()
            .time_since_epoch()
            .count();

    shuffle(deck_of_cards.begin(), deck_of_cards.end(), std::default_random_engine(seed));
}

/**
* Distribution des cartes
 */

void Deck::distributeCards(int nbCards, const vector<Player *> &players) {
    for(Player* player: players){
        for(int i = 0; i < nbCards; i++){
            player->addCard(this->getCard());
        }
    }
}