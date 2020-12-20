#include "ColoredCard.hpp"

ColoredCard::ColoredCard(string n, int id, int p, COLOR c) : Card(std::move(n), id, p), color(c)
{
}

ColoredCard::~ColoredCard() = default;

COLOR ColoredCard::getColor() const {
    return color;
}


