#ifndef CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
#define CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP


#include "Game.hpp"
#include "ColoredCard.hpp"

class HuitAmericain : Game {

protected:
    Card *cardOnTop{};
    COLOR actualColor = NONE;
    bool sensInverse;

    int actualPlaying = 0;
public:
    HuitAmericain(const Deck &deck);

private:
    void initGame() override;

    void startGame() override;

    bool isWinner() override;

    int getWinner() override;

    int getIndexOfParseCard() override;

    void playRound(int indexCardToPlay) override;

    void distributeCards() override;

};

#endif //CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
