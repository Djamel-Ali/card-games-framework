#include "Card.hpp"

Card::Card(const string &_name, int _id, int _value) : name(_name), id(_id), value(_value) {
}

Card::~Card() = default;

int Card::getId() const {
    return id;
}

string Card::getName() const {
    return name;
}

int Card::getValue() const {
    return value;
}


