#include "Player.hpp"
#include "ColoredCard.hpp"
#include <iostream>

// Ctor
Player::Player(const string &_name, const vector<Card*> &_hand, float _score = 0, bool _bot = false) : name(_name), hand(_hand), current_score(_score), bot(_bot) {}

//Dtor
Player::~Player(){
    for(Card * temp : hand){
        delete temp;
    }
}

// Getters Setters :

const string &Player::getName() const {
    return name;
}

const vector<Card*> &Player::getHand() const {
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

void Player::displayHand() {
    cout << "\nLa main de " << getName() << " : " << endl;
    auto counter = -1;
    for (Card *pCard: hand) {
        auto temp = dynamic_cast<ColoredCard*>(pCard);
        if (temp)
            cout << "(" << ++counter << "): " << *temp << " ; ";
        else
            cout << "(" << ++counter << "): " << *pCard << " ; ";
    }
    cout <<"\n" << endl;
}

bool Player::isBot() const {
    return bot;
}

std::ostream &operator<<(std::ostream &out, const Player &a_player) {
    out << "\n\n\t" << a_player.getName()
        << " ======> Score : " << (float)a_player.getCurrentScore() << endl;
    return out;
}
