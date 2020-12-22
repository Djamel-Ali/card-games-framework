#ifndef CARD_GAMES_FRAMEWORK_UNO_HPP
#define CARD_GAMES_FRAMEWORK_UNO_HPP

#include "Game.hpp"
#include "Card.hpp"
#include "ColoredCard.hpp"

class UNO : public Game{

protected:
    Card* cardOnTop{};
    bool sensInverse;
    int actualPlaying = -1;

public:
    explicit UNO(const Deck &deck);
    void initGame() override;
    void startGame() override;

    // cherche dans la liste des joueurs actuels s'il y a un gagnant
    bool isWinner() override;

    // retourne l'index du gagnant dans la liste des joueurs
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


#endif //CARD_GAMES_FRAMEWORK_UNO_HPP
