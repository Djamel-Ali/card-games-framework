#ifndef CARD_GAMES_FRAMEWORK_DECK_HPP
#define CARD_GAMES_FRAMEWORK_DECK_HPP


#include <vector>
#include "Card.hpp"
#include "Player.hpp"

class Deck {
private:
    vector<Card*> deck_of_cards;

public:
    // Ctor Dtor
    Deck();
    ~Deck();

    // Getters :
    vector<Card*> &getDeckOfCards();
    Card* getCard();

    // Other methods :
    void addCard(Card *pCard);
    void shuffleCards();
    void distributeCards(int nbCards, const vector<Player*> &players);
};


#endif //CARD_GAMES_FRAMEWORK_DECK_HPP
