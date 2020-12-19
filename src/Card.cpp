#include "Card.hpp"

Card::Card(string n, int v, int p) : name(std::move(n)),value(v), point(p)
{
}

Card::~Card() = default;

int Card::getValue() const {
    return value;
}

string Card::getName() const {
    return name;
}

int Card::getPoint() const {
    return point;
}


