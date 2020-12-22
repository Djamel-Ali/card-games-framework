#ifndef CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
#define CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP

#include "Game.hpp"
#include "Card.hpp"
#include "ColoredCard.hpp"

class HuitAmericain : public Game{

protected:
    Card* cardOnTop{};
    bool sensInverse{};
    int actualPlaying = -1;
    COLOR* colors;

public:
    explicit HuitAmericain(const Deck &deck);
    void createCards() override;
    void startGame() override;
    bool isWinner() override;
    int getWinner() override;
    int getIndexOfParseCard() override;
    void playRound(int indexCardToPlay) override;

    void nextPlayer();
    void plusTwo();
    void plusFour();
    void reversed();
    void changeColor();
    bool cardPlayable(Card* toPlay);
    bool playerCanPlay(const vector<Card*>& hand);
};


#endif //CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
