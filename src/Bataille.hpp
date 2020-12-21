#ifndef CARD_GAMES_FRAMEWORK_BATAILLE_HPP
#define CARD_GAMES_FRAMEWORK_BATAILLE_HPP

#include "Game.hpp"
#include "Card.hpp"

class Bataille : public Game {

protected:
    vector<Card *> tapis;
    bool ohBataille;

public:
    Bataille();

    void initGame() override;

    void startGame() override;

    bool isWinner() override;

    int getWinner() override;

    int getIndexOfParseCard() override;

    void playRound(int indexCardToPlay) override;

    void distributeCards() override;

};


#endif //CARD_GAMES_FRAMEWORK_BATAILLE_HPP
