#ifndef CARD_GAMES_FRAMEWORK_PLAYER_HPP
#define CARD_GAMES_FRAMEWORK_PLAYER_HPP

#include <string>
#include <vector>

#include "Card.hpp"

using namespace std;

class Player {

private:
    string name;
    vector<Card*> hand;
    float current_score;
    bool bot;
public:
    // Ctor Dtor
    Player(const string &_name, const vector<Card*> &_hand, float _score, bool _bot);
    ~Player();

    //Getters Setters :
    const string &getName() const;
    const vector<Card*> &getHand() const;
    float getCurrentScore() const;
    void setCurrentScore(float score);

    // Other methods :
    bool handEmpty();
    Card* playCard(int index);
    void addCard(Card* toAdd);
    bool isBot() const;
    void displayHand();
};

/// Surcharge de l’opérateur <<
std::ostream &operator<<(std::ostream &out, const Player &a_game);


#endif //CARD_GAMES_FRAMEWORK_PLAYER_HPP
