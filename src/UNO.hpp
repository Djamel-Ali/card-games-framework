#ifndef CARD_GAMES_FRAMEWORK_UNO_HPP
#define CARD_GAMES_FRAMEWORK_UNO_HPP

#include "Game.hpp"
#include "Card.hpp"
#include "ColoredCard.hpp"

class UNO : public Game{

protected:
    Card* cardOnTop{};
    COLOR actualColor = NONE;
    bool sensInverse;
    int actualPlaying = 0;

public:
    explicit UNO(const Deck &deck);
    void initGame() override;
    void startGame() override;
    bool isWinner() override;
    int getWinner() override;
    int whichCardWins() override;
    void playRound() override;
    void distributeCards() override;

    void nextPlayer();
    void plusTwo(int playerIndex);
    void plusFour(int playerIndex);
    void reversed();
    void changeColor();

    bool cardPlayable(Card* toPlay);

};


#endif //CARD_GAMES_FRAMEWORK_UNO_HPP
