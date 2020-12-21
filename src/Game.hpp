#ifndef CARD_GAMES_FRAMEWORK_GAME_HPP
#define CARD_GAMES_FRAMEWORK_GAME_HPP

#include <vector>
#include "Deck.hpp"
#include "Player.hpp"

using namespace std;


class Game {

protected:
    vector<Player *> joueurs;
    Deck deck;
public:
    explicit Game(const Deck &_deck);

    virtual void initGame() = 0;

    virtual void startGame() = 0;

    virtual bool isWinner() = 0;

    virtual int getWinner() = 0;

    virtual int whichCardWins() = 0;

};


#endif //CARD_GAMES_FRAMEWORK_GAME_HPP
