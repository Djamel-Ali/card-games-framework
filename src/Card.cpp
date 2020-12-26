#include "Card.hpp"
#include <iostream>

using namespace std;

Card::Card(const string &_name, int _id, float _value) : name(_name), id(_id), value(_value) {

}

Card::~Card() = default;

int Card::getId() const {
    return id;
}

string Card::getName() const {
    return name;
}

float Card::getValue() const {
    return value;

}

bool Card::operator==(const Card &other) const {
    cout << "== de Card \n";
    return this->value == other.value;
}

bool Card::operator>(const Card &other) const {
    return this->value > other.getValue();
}

ostream &operator<<(ostream &out, const Card &card) {

    out << card.getName();
    // Pour simplifier l'affichage des cartes au joueur, il vaut mieux ne pas afficher id et value.
//    out << card.getId() << "\n";
//    out << card.getValue() << "\n";

    return out;
}
