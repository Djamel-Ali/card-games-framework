#ifndef CARD_GAMES_FRAMEWORK_GAME_HPP
#define CARD_GAMES_FRAMEWORK_GAME_HPP

#include <vector>
class Player;
class Deck;
using namespace std;


class Game {
    private:
        vector <Player*> joueurs;
        Deck deck;
    public:
        Game();

        virtual void initGame() = 0;
        virtual void startGame() = 0;
        virtual bool isWinner() = 0;
        virtual int getWinner() = 0;
        virtual int whichCardWins() = 0;

};


#endif //CARD_GAMES_FRAMEWORK_GAME_HPP
