#ifndef CARD_GAMES_FRAMEWORK_TAROT_HPP
#define CARD_GAMES_FRAMEWORK_TAROT_HPP


#include "Card.hpp"
#include "Game.hpp"
#include "ColoredCard.hpp"

class Tarot : public Game {
private:
    vector<Card *> tapis;
    vector<Card *> chien;
    COLOR *colors;


public:
    Tarot(const Deck &deck);

    bool isWinner() override;

    int getWinner() override;

    int getIndexOfParseCard() override;

    void playRound(int indexCardToPlay) override;

    void nextPlayer();

    void createCards() override;

    void startGame() override;

    const vector<Card *> &getChien() const;

    void setChien(const vector<Card *> &_chien);
};


#endif //CARD_GAMES_FRAMEWORK_TAROT_HPP
