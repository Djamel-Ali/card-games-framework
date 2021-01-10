#include "Player.hpp"

// Ctor
Player::Player(const string &_name, const vector<Card*> &_hand, int _score = 0) : name(_name), hand(_hand), current_score(_score) {}

//Dtor
Player::~Player(){
    for(Card * temp : hand){
        delete temp;
    }
}

// Getters Setters :

string &Player::getName() {
    return name;
}

vector<Card*> &Player::getHand() {
    return hand;
}

//retourne le score du joueur
float Player::getCurrentScore() const {
    return current_score;
}

void Player::setCurrentScore(float score) {
    current_score = score;
}

// Other methods :

/**
* retourne si la main est vide (un joueur n'a plus de carte)
 */

bool Player::handEmpty() {
    return hand.empty();
}

/**
* return une carte et la supprime de la main (avec l'index)
 */

Card *Player::playCard(int index) {
    Card* temp = hand.at(index);

    hand.erase(hand.begin() + index);

    return temp;
}

/**
* ajouter une carte à la main
 */

void Player::addCard(Card *toAdd) {
    hand.push_back(toAdd);
}
