#ifndef CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
#define CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP

#include "Card.hpp"

class ColoredCard : public Card{

private:
    string color;

public:
    ColoredCard(string n, int id, int p, string c);
    ~ColoredCard();

    string getColor() const;
};


#endif //CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
