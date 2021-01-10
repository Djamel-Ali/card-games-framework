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
    explicit HuitAmericain(Deck *_deck);
    ~HuitAmericain() override;

    void plusTwo();
    void plusFour();
    void reversed();
    void changeColor();
    bool cardPlayable(Card* toPlay);
    bool playerCanPlay(const vector<Card*>& hand);
    void setPoints(int iPlayer);

    void createCards() override;
    void distribution() override;
    bool isWinner() override;
    int getWinner() override;
    int getIndexOfParseCard() override;
    void playRound(int indexCardToPlay) override;
    void nextPlayer() override;
    void print(ostream& out) override;
};


#endif //CARD_GAMES_FRAMEWORK_HUITAMERICAIN_HPP
