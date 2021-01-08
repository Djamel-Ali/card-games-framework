#ifndef CARD_GAMES_FRAMEWORK_GAME_HPP
#define CARD_GAMES_FRAMEWORK_GAME_HPP

#include <vector>
#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"

using namespace std;

class Game {

private:

protected:
    Deck deck;
    vector <Player*> joueurs;
    const string name;

public:
    explicit Game(const Deck &_deck);
    void initGame(); // mise en commun
    static Card *getCardById(const vector<Card*> &vect_of_cards, int card_id);
    static void moveFromTo(vector<Card*> src, vector<Card*> dest);

    virtual void createCards() = 0;
    virtual void startGame() = 0; // a mettre en commun plus tard
    virtual bool isWinner() = 0; // a mettre en commun plus tard (pour bataille, uno et 8us)
    virtual int getWinner() = 0; // a mettre en commun plus tard (pour bataille, uno et 8us)
    virtual int getIndexOfParseCard() = 0;
    virtual void playRound(int indexCardToPlay) = 0;
    virtual string getName() const = 0;
    virtual Player *getPlayerByID(int _id) = 0;

};


#endif //CARD_GAMES_FRAMEWORK_GAME_HPP
