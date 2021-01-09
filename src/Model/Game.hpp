#ifndef CARD_GAMES_FRAMEWORK_GAME_HPP
#define CARD_GAMES_FRAMEWORK_GAME_HPP

#include <vector>
#include "Deck.hpp"
#include "Player.hpp"

using namespace std;

class Game {

protected:
    Deck deck;
    vector <Player*> joueurs;
    int actualPlaying = 0;
public:
    explicit Game(const Deck &_deck);
    void initGame(); // mise en commun
    Player* getActualPlaying() const;


    virtual void createCards() = 0;
    virtual void startGame() = 0; // a mettre en commun plus tard
    virtual bool isWinner() = 0; // a mettre en commun plus tard (pour bataille, uno et 8us)
    virtual int getWinner() = 0; // a mettre en commun plus tard (pour bataille, uno et 8us)
    virtual int getIndexOfParseCard() = 0;
    virtual void playRound(int indexCardToPlay) = 0;
    virtual void nextPlayer() = 0;
    virtual void print(ostream& out) = 0;

    friend ostream& operator<<(ostream& out, Game &game);
};


#endif //CARD_GAMES_FRAMEWORK_GAME_HPP
