#ifndef CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
#define CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP

#include "../Game.hpp"
#include "../ColoredCard.hpp"


class HuitAmericain : public Game{

protected:
    Card* cardOnTop;
    bool sensInverse = false;
    COLOR* colors;

public:
    explicit HuitAmericain(Deck *_deck, int player);
    void createCards() override;
    bool isWinner() override;
    int getWinner() override;
    int getIndexOfParseCard() override;
    void playRound(int indexCardToPlay) override;
    void print(ostream& out) override;
    void nextPlayer() override;
    void distribution() override;

    void startGame();
    void plusTwo();
    void plusFour();
    void reversed();
    void changeColor();
    bool cardPlayable(Card* toPlay);
    bool playerCanPlay(const vector<Card*>& hand);
    void setPoints(int iPlayer);

};


#endif //CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
