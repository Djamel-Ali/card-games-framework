#ifndef CARD_GAMES_FRAMEWORK_GAME_HPP
#define CARD_GAMES_FRAMEWORK_GAME_HPP

#include <vector>
#include "Deck.hpp"
#include "Player.hpp"

using namespace std;

class Game {

protected:
    Deck *deck;
    vector <Player*> joueurs;
    int actualPlaying;
    vector<Card *> tapis;
public:
    //ctor dtor
    explicit Game(Deck *deck);
    virtual ~Game();

    //getters
    Player* getActualPlaying() const;
    Player* getPlayer(int iPlayer) const;

    //fonctions en commun
    void initGame();
    void startGame();
    void playRound(int indexCardToPlay);
    //fonctions virtual
    virtual bool playerCanPlay();
    virtual bool cardPlayable(Card* toPlay);

    //fonctions pures
    virtual void createCards() = 0;
    virtual void distribution() = 0;
    virtual bool isWinner() = 0;
    virtual int getWinner() = 0;
    virtual int getIndexOfParseCard() = 0;
    virtual void nextPlayer() = 0;
    virtual void print(ostream& out) = 0;

    int playAuto();
    friend ostream& operator<<(ostream& out, Game &game);
};


#endif //CARD_GAMES_FRAMEWORK_GAME_HPP
