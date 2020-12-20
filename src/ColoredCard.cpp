#include "ColoredCard.hpp"

ColoredCard::ColoredCard(string n, int id, int p, string c) : Card(std::move(n), id, p), color(std::move(c))
{
}

ColoredCard::~ColoredCard() = default;

string ColoredCard::getColor() const {
    return color;
}
