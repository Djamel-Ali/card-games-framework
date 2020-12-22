#include "ColoredCard.hpp"
#include <iostream>

ColoredCard::ColoredCard(const string &_name, int id, int _value, COLOR _color) :
        Card((_name), id, _value), color(_color) {}

ColoredCard::~ColoredCard() = default;

COLOR ColoredCard::getColor() const {
    return color;
}

bool ColoredCard::operator==(const ColoredCard &other) const {
    cout << "== de ColoredCard \n";

    return this->getValue() == other.getValue() || this->color == other.color || other.color == NONE;
}

ostream &operator<<(ostream &out, const ColoredCard &fs) {

    out << fs.getName() <<"\n";
    out << fs.getId() <<"\n";
    out << fs.getValue() <<"\n";
    out << fs.getColor() <<"\n";

    return out;
}



