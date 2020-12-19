#include "ColoredCard.hpp"

ColoredCard::ColoredCard(string n, int v, int p, string c) : Card(std::move(n), v, p), color(std::move(c))
{
}

ColoredCard::~ColoredCard() = default;

string ColoredCard::getColor() const {
    return color;
}
