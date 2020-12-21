#ifndef CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
#define CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP

#include "Game.hpp"
#include "Card.hpp"
#include "ColoredCard.hpp"

class HuitAmericain : public Game{

protected:
    Card* cardOnTop{};
    bool sensInverse;
    int actualPlaying = -1;
    COLOR actualColor = NONE;


public:
    explicit HuitAmericain(const Deck &deck);
    void initGame() override;
    void startGame() override;
    bool isWinner() override;
    int getWinner() override;
    int getIndexOfParseCard() override;
    void playRound(int indexCardToPlay) override;
    void distributeCards() override;

    void nextPlayer();
    void plusTwo();
    void plusFour();
    void reversed();
    void changeColor();

    bool cardPlayable(Card* toPlay);

};


#endif //CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
