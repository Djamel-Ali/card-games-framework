#ifndef CARD_GAMES_FRAMEWORK_UNO_HPP
#define CARD_GAMES_FRAMEWORK_UNO_HPP

#include "Game.hpp"
#include "Card.hpp"

class UNO : public Game{

protected:
    Card cardOnTop;

public:
    UNO();
    void initGame() override;
    void startGame() override;
    bool isWinner() override;
    int getWinner() override;
    int whichCardWins() override;
    void playRound() override;
    void distributeCards() override;
};


#endif //CARD_GAMES_FRAMEWORK_UNO_HPP
