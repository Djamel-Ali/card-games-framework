#include <iostream>
#include "Player.hpp"

// Initialization of static var
int Player::player_id_counter = 0;

// Ctor
Player::Player(const int _uid, const string &_name, const vector<Card *> &_hand, int _score) : unique_id(
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

vector<Card *> &Player::getHand() {
    return hand;
}

int Player::getCurrentScore() const {
    return current_score;
}

int Player::getFinalScore() const {
    return final_score;
}

// Setters :

void Player::setCurrentScore(float _score) {
    current_score = _score;
}

void Player::setFinalScore(int finalScore) {
    final_score = finalScore;
}

void Player::setHand(const vector<Card *> &_hand) {
    Player::hand = _hand;
}

// Other methods :

bool Player::handEmpty() {
    return hand.empty();
}

//todo : Player::playCard(arg) : il faut se mettre d'accord si on passe l'index ou l'ID en arg
Card *Player::playCard(int index) {
    Card *temp = hand.at(index);

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

void Player::displayHand() const {
    cout << "HAND : ";
    auto counter = -1;
    for (Card *pCard: hand) {
        cout << "(" << counter++ << "): " << *pCard << " ; ";
    }
}

// Remettre les cartes de la main du joueur courant dans le Deck passé en arg
void Player::putBackHand(Deck &_deck) {
    if(!handEmpty())
    {
        _deck.getDeckOfCards().insert(_deck.getDeckOfCards().end(), hand.begin(), hand.end());
        hand.clear();
    }
}

// Remettre les cartes gagnées dans la pioche (passée en arg)
void Player::putBackReserve(Deck &_deck) {
    if(!reserve.empty())
    {
        _deck.getDeckOfCards().insert(_deck.getDeckOfCards().end(), reserve.begin(), reserve.end());
        reserve.clear();
    }
}

vector<Card *> Player::getReserve() const {
    return reserve;
}

void Player::setReserve(const vector<Card *> &_reserve) {
    Player::reserve = _reserve;
}

int Player::getIndexOfCardToPlay() {
    int chosen_index = -1;

    //Afficher la main du joueur pour qu'il puisse choisir la carte à jouer
    displayHand();

    do {
        cout << "Saisissez l'indice de la carte à jouer svp : ";
        cin >> chosen_index;
    }while (chosen_index < 0 or chosen_index > hand.size()-1);

    return chosen_index;
}


std::ostream &operator<<(std::ostream &out, const Player &a_player) {
    out << "\n\n\t" << a_player.getName() << " (id = " << a_player.getUniqueId() << ") "
        << " ======> Score : " << a_player.getFinalScore() << endl;
    return out;
}
