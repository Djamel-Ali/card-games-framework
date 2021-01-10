#ifndef CARD_GAMES_FRAMEWORK_PLAYER_HPP
#define CARD_GAMES_FRAMEWORK_PLAYER_HPP


#include <string>
#include <vector>

#include "Card.hpp"

using namespace std;

class Player {

private:
    const int unique_id;
    string name;
    vector<Card*> hand;
    int current_score;
public:

    // Ctor
    Player(int _uid, const string &_name, const vector<Card*> &_hand, int _score);

    // Dtor
    ~Player();

    //Getters :

    int getUniqueId() const;

    const string &getName() const;

    const vector<Card*> &getHand() const;

    int getCurrentScore() const;

    // Setters :

    void setCurrentScore(int score);

    // Other methods :

    bool handEmpty();

    Card* playCard(int index);

    void addCard(Card* toAdd);
};


#endif //CARD_GAMES_FRAMEWORK_PLAYER_HPP
