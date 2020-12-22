#ifndef CARD_GAMES_FRAMEWORK_GAME_HPP
#define CARD_GAMES_FRAMEWORK_GAME_HPP

#include "Card.hpp"
#include <vector>
#include "Deck.hpp"
#include "Player.hpp"

class Game {

private:

protected:
    Deck deck;
    vector <Player*> joueurs;

public:
    explicit Game(const Deck &_deck);

    virtual void initGame() = 0;

    virtual void startGame() = 0;

    virtual bool isWinner() = 0;

    virtual int getWinner() = 0;

    virtual int getIndexOfParseCard() = 0;
    virtual void playRound(int indexCardToPlay) = 0;
    virtual void distributeCards() = 0;
};


#endif //CARD_GAMES_FRAMEWORK_GAME_HPP
