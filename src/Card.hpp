#ifndef CARD_GAMES_FRAMEWORK_CARD_HPP
#define CARD_GAMES_FRAMEWORK_CARD_HPP

#include <string>
using namespace std;

class Card {
    private:
        const string name;
        const int id;

        int value; // non const car les points des cartes de la belote changent quand ils sont atouts !

    public:
        Card(string _name, int _id, int _value);
        ~Card();

        int getId() const;
        string getName() const;
        int getValue() const;
        bool operator==(Card const & other) const;
        bool operator>(Card const & other) const;
};


#endif //CARD_GAMES_FRAMEWORK_CARD_HPP
