#include "Card.hpp"

Card::Card(string n, int id, int p) : name(std::move(n)),ID(id), point(p)
{
}

Card::~Card() = default;

int Card::getID() const {
    return ID;
}

string Card::getName() const {
    return name;
}

int Card::getPoint() const {
    return point;
}


