#include <iostream>
#include "Player.hpp"

// Initialization of static var
int Player::player_id_counter = 0;

// Ctor
Player::Player(const int _uid, const string &_name, const vector<Card*> &_hand, int _score) : unique_id(
        _uid), name(_name), hand(_hand), current_score(_score) {}

// copy ctor
Player::Player(const Player &player) = default;

//Dtor
Player::~Player() = default;

// Getters :

int Player::getUniqueId() const {
    return unique_id;
}

const string &Player::getName() const {
    return name;
}

vector<Card*> &Player::getHand() {
    return hand;
}

int Player::getCurrentScore() const {
    return current_score;
}

// Setters :

void Player::setCurrentScore(int score) {
    current_score = score;
}

void Player::setHand(const vector<Card *> &_hand) {
    Player::hand = _hand;
}

// Other methods :

bool Player::handEmpty() {
    return hand.empty();
}

Card *Player::playCard(int index) {
    Card* temp = hand.at(index);

    hand.erase(hand.begin() + index);

    return temp;
}

// ajoute la carte (au fait c'est son pointeur) passée en argument à la main du joueur courant
void Player::addCard(Card *toAdd) {
    hand.push_back(toAdd);
}

int Player::get_fresh_player_uid() {
    return player_id_counter++;
}

void Player::displayHand() {
    cout << "HAND : ";
    for(Card *pCard: hand){
        cout << *pCard << " ; ";
    }
}
// Remettre les cartes de la main du joueur courant dans le Deck passé en arg
void Player::putBackHand(Deck& _deck) {
    _deck.getDeckOfCards().insert(_deck.getDeckOfCards().end(),hand.begin(), hand.end());
    hand.clear();
}
