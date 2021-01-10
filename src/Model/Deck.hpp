#ifndef CARD_GAMES_FRAMEWORK_DECK_HPP
#define CARD_GAMES_FRAMEWORK_DECK_HPP


#include <vector>
#include "Card.hpp"
#include "Player.hpp"
using namespace std;

class Deck {
private:
    vector<Card*> deck_of_cards;

public:
    // Ctor
    Deck();

    // Dtor
    ~Deck();

    // Getters :
    const vector<Card*> &getDeckOfCards() const;

    // Other methods :
    void addCard(Card *pCard);

    Card* getCard();

    void shuffleCards();

    void distributeCards(int nbCards, const vector<Player*> &players);
};


#endif //CARD_GAMES_FRAMEWORK_DECK_HPP
