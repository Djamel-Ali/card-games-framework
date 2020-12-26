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
    Deck(const vector<Card*> &_deckOfCards);

    // Dtor
    virtual ~Deck();

    // Getters and Setters :
    vector<Card*> &getDeckOfCards() const;

    void setDeckOfCards(const vector<Card *> &_deckOfCards);

    // Other methods :
    void addCard(Card *pCard);

    // Renvoie la carte qui est au sommet de la pioche et la supprime de cette dernière
    Card* getCard();

    void shuffleCards();

    void distributeCards(int nbCards, const vector<Player*> &players);
};


#endif //CARD_GAMES_FRAMEWORK_DECK_HPP
