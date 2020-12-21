#ifndef CARD_GAMES_FRAMEWORK_BATAILLE_HPP
#define CARD_GAMES_FRAMEWORK_BATAILLE_HPP

#include "Game.hpp"
#include "Card.hpp"

class Bataille : public Game {

protected:
    vector<Card *> tapis;
    bool ohBataille;

public:
    Bataille() : Game(Deck(std::vector<Card>())) {}

    void initGame() override;

    void startGame() override;

    bool isWinner() override;

    int getWinner() override;

    int whichCardWins() override;

    void playRound() override;

    void distributeCards() override;

};


#endif //CARD_GAMES_FRAMEWORK_BATAILLE_HPP
