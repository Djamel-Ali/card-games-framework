#ifndef CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
#define CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP

#include "Game.hpp"
#include "Card.hpp"
#include "ColoredCard.hpp"

class HuitAmericain : public Game{

protected:
    Card* cardOnTop{};
    bool sensInverse{};
    COLOR* colors;

public:
    explicit HuitAmericain(const Deck &deck);
    void createCards() override;
    void startGame() override;
    bool isWinner() override;
    int getWinner() override;
    int getIndexOfParseCard() override;
    void playRound(int indexCardToPlay) override;
    void print(ostream& out) override;
    void nextPlayer() override;

    void plusTwo();
    void plusFour();
    void reversed();
    void changeColor();
    bool cardPlayable(Card* toPlay);
    bool playerCanPlay(const vector<Card*>& hand);
    void setPoints(int iPlayer);

    int actualPlaying = -1;
};


#endif //CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
