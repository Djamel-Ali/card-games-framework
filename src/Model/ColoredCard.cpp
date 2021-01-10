#include "ColoredCard.hpp"
#include <iostream>

ColoredCard::ColoredCard(const string &_name, int id, float _value, COLOR _color) :
        Card((_name), id, _value), color(_color) {}

ColoredCard::~ColoredCard() = default;

COLOR ColoredCard::getColor() const {
    return color;
}

void ColoredCard::setValue(float v) {
    value = v;
}

bool ColoredCard::operator==(const ColoredCard &other) const {
    return this->getValue() == other.getValue() || this->color == other.color || other.color == NONE;
}

ostream &operator<<(ostream &out, const ColoredCard &fs) {
    out << " [ " << fs.getName() << " | " << fs.getColor() << " ] ";

    return out;
}

