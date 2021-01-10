#ifndef CARD_GAMES_FRAMEWORK_BATAILLE_HPP
#define CARD_GAMES_FRAMEWORK_BATAILLE_HPP

#include "../Game.hpp"
#include "../Card.hpp"

class Bataille : public Game {

protected:
    vector<Card *> tapis;
    bool ohBataille;

public:
    Bataille(Deck *deck);

    void createCards() override;

    bool isWinner() override;
    int getWinner() override;
    int getIndexOfParseCard() override;
    void playRound(int indexCardToPlay) override;
    void nextPlayer() override;
    void print(ostream& out) override;
    void distribution() override;

    void startGame();
    void decideWinner();

};


#endif //CARD_GAMES_FRAMEWORK_BATAILLE_HPP
