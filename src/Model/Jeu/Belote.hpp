#ifndef CARD_GAMES_FRAMEWORK_BELOTE_HPP
#define CARD_GAMES_FRAMEWORK_BELOTE_HPP

#include "../Game.hpp"
#include "../ColoredCard.hpp"

class Belote : public Game{

protected:
    COLOR atout; // couleur de l'atout du round
    COLOR fold; // couleur du pli
    int lastFoldWinner; // dernier vinqueur d'un pli
    int ordreDeJeu = 0;
    int tempScore[2]{0 ,0};
    //Card* tapis[4]{};

public:
    explicit Belote(Deck *_deck);

    bool cardPlayable(Card* toPlay) override;
    bool playerHaveColor(COLOR color);
    void setCardsAtout();
    void setPoints();
    int getlastWinner();

    void createCards() override;
    void distribution() override;
    bool isWinner() override;
    int getWinner() override;
    int getIndexOfParseCard() override;
    void nextPlayer() override;
    void print(ostream& out) override;

};


#endif //CARD_GAMES_FRAMEWORK_BELOTE_HPP
