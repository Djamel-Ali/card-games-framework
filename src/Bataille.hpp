#ifndef CARD_GAMES_FRAMEWORK_BATAILLE_HPP
#define CARD_GAMES_FRAMEWORK_BATAILLE_HPP
#include "Game.hpp"
#include "Card.hpp"
class Bataille : public Game{

private:


public:
     void initGame() override;
     void startGame() override;
     bool isWinner() override;
     int getWinner() override;
     int whichCardWins() override;


};


#endif //CARD_GAMES_FRAMEWORK_BATAILLE_HPP
