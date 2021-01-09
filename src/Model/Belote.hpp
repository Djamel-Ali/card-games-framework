#ifndef CARD_GAMES_FRAMEWORK_BELOTE_HPP
#define CARD_GAMES_FRAMEWORK_BELOTE_HPP

#include "Game.hpp"
#include "ColoredCard.hpp"

class Belote : public Game{

protected:
    COLOR atout; // couleur de l'atout du round
    COLOR fold; // couleur du pli
    int lastFoldWinner; // dernier vinqueur d'un pli
    int ordreDeJeu = 0;
    int tempScore[2]{};
    Card* tapis[4]{};

public:
    explicit Belote(const Deck &deck);
    void createCards() override;
    void startGame() override;
    bool isWinner() override;
    int getWinner() override;
    int getIndexOfParseCard() override;
    void playRound(int indexCardToPlay) override;
    void print(ostream& out) override;
    void nextPlayer() override;
    bool cardPlayable(Card* toPlay);
    bool playerHaveColor(COLOR color);
    void setCardsAtout();
    void setPoints();
    void distribution();
};


#endif //CARD_GAMES_FRAMEWORK_BELOTE_HPP
