#include "Card.hpp"

Card::Card(string _name, int _id, int _value) : name(std::move(_name)), id(_id), value(_value)
{
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

bool Card::operator==(const Card &other) const {
    return this->value == other.getValue();
}

bool Card::operator>(const Card &other) const {
    return this->value > other.getValue();
}


