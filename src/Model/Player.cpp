#include "Player.hpp"

// Ctor
Player::Player(const int _uid, const string &_name, const vector<Card*> &_hand, int _score = 0) : unique_id(
        _uid), name(_name), hand(_hand), current_score(_score) {}

//Dtor
Player::~Player(){
    for(Card * temp : hand){
        delete temp;
    }
}

// Getters :

int Player::getUniqueId() const {
    return unique_id;
}

const string &Player::getName() const {
    return name;
}

const vector<Card*> &Player::getHand() const {
    return hand;
}

//retourne le score du joueur
int Player::getCurrentScore() const {
    return current_score;
}

// Setters :

void Player::setCurrentScore(int score) {
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
