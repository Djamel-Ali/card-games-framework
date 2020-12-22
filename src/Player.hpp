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

    // Used by the get_fresh_player_uid() method to generate unique IDs
    static int player_id_counter;

    // Generates a new identifier for each call that is different from the previous ones returned.
    static int get_fresh_player_uid();

public:

    // Ctor
    Player(int _uid, const string &_name, const vector<Card*> &_hand, int _score);

    // Dtor
    virtual ~Player();

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
