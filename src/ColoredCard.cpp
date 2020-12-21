#include "ColoredCard.hpp"

ColoredCard::ColoredCard(const string &_name, int id, int _value, COLOR _color) :
        Card((_name), id, _value), color(_color) {}

ColoredCard::~ColoredCard() = default;

COLOR ColoredCard::getColor() const {
    return color;
}

bool ColoredCard::operator==(const ColoredCard &other) const {
    return Card::operator==(other) || this->color == other.color || this->color == NONE;
}


