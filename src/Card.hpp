#ifndef CARD_GAMES_FRAMEWORK_CARD_HPP
#define CARD_GAMES_FRAMEWORK_CARD_HPP

#include <string>


using namespace std;

class Card {
private:
    const string name;
    const int id;
    float value; // non const car les points des cartes de la belote changent quand ils sont atouts !

public:
    // Ctor and Dtor :
    Card(const string &_name, int _id, float _value);

    ~Card();

    // Getters and Setters :
    int getId() const;

    string getName() const;
    float getValue() const;
    virtual bool operator== (Card const & other) const;
    virtual bool operator> (Card const & other) const;
    friend ostream& operator<<(ostream& out, const Card &card);
};


#endif //CARD_GAMES_FRAMEWORK_CARD_HPP
