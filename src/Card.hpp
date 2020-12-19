#ifndef CARD_GAMES_FRAMEWORK_CARD_HPP
#define CARD_GAMES_FRAMEWORK_CARD_HPP

#include <string>
using namespace std;

class Card {
    private:
        const string name;
        const int value;

        int point; // non const car les points des cartes de la belote changent quand ils sont atouts !
    public:
        Card(string n, int v, int p);
        ~Card();

        int getValue() const;
        string getName() const;
        int getPoint() const;
};


#endif //CARD_GAMES_FRAMEWORK_CARD_HPP
