#include "Card.hpp"
#include <iostream>

using namespace std;

Card::Card(const string &_name, int _id, int _value) : name(_name), id(_id), value(_value) {

}

Card::~Card() {

}

int Card::getId() const {
    return id;
}

string Card::getName() const {
    return name;
}

int Card::getValue() const {
    return value;
}

bool Card::operator==(const Card &other) const {

    return this->value == other.value;
}

bool Card::operator>(const Card &other) const {

    return this->value > other.getValue();
}

ostream &operator<<(ostream &out, const Card &fs) {
    out << " [ " << fs.getName() << " | " << fs.getValue() << " ] " << endl;

    return out;
}







