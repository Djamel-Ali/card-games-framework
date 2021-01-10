#include "ColoredCard.hpp"
#include <iostream>

ColoredCard::ColoredCard(const string &_name, int id, int _value, COLOR _color) :
        Card((_name), id, _value), color(_color) {}

ColoredCard::~ColoredCard() = default;

COLOR ColoredCard::getColor() const {
    return color;
}



bool ColoredCard::operator==(const ColoredCard &other) const {
    return this->getValue() == other.getValue() || this->color == other.color || other.color == NONE;
}

ostream &operator<<(ostream &out, const ColoredCard &fs) {
    out << " [ " << fs.getName() << " | " << fs.getColor() << " ] " << endl;

    return out;
}

void ColoredCard::setValue(int v) {
    value = v;
}



