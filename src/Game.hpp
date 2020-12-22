#ifndef CARD_GAMES_FRAMEWORK_GAME_HPP
#define CARD_GAMES_FRAMEWORK_GAME_HPP

#include <vector>
#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"

using namespace std;

using namespace std;


class Game {

private:

protected:
    Deck deck;
    vector <Player*> joueurs;

public:
    explicit Game(const Deck &_deck);
    void initGame();

    virtual void createCards() = 0;
    virtual void startGame() = 0;
    virtual bool isWinner() = 0;
    virtual int getWinner() = 0;
    virtual int getIndexOfParseCard() = 0;
    virtual void playRound(int indexCardToPlay) = 0;

};


#endif //CARD_GAMES_FRAMEWORK_GAME_HPP
