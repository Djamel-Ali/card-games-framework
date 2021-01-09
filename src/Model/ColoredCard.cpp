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

    out << " --- " << endl;
    out << "| " << fs.getName()<<" |" << endl;
    out << "| " <<fs.getColor()<<" |" << endl;
    out << "| " <<fs.getValue()<<" |" << endl;
    out << " --- " << endl;

    return out;
}

void ColoredCard::setValue(int v) {
    value = v;
}



