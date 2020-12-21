#ifndef CARD_GAMES_FRAMEWORK_DECK_HPP
#define CARD_GAMES_FRAMEWORK_DECK_HPP


#include <vector>
#include "Card.hpp"

class Deck {
private:
    std::vector<Card> deck_of_cards;

public:
    // Ctor
    Deck(const vector<Card> &_deckOfCards);

    // Dtor
    virtual ~Deck();

    // Getters :
    const vector<Card> &getDeckOfCards() const;

    // Other methods :
    void addCard(Card *pCard);
};


#endif //CARD_GAMES_FRAMEWORK_DECK_HPP
