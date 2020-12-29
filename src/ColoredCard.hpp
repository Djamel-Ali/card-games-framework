#ifndef CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
#define CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP

#include "Card.hpp"
#include <iostream>

enum COLOR {
    BLEU, VERT, JAUNE, ROUGE, TREFLE, COEUR, CARREAU, PIQUE , NONE
};

class ColoredCard : public Card {

private:
    COLOR color;

public:
    ColoredCard(const string &_name, int id, float _value, COLOR _color);

    ~ColoredCard();

    COLOR getColor() const;

    virtual bool operator==(ColoredCard const & other) const;

    friend ostream& operator<<(ostream& out, const ColoredCard &coloredCard);

    friend ostream& operator<<(ostream& out, const COLOR &colo);

    virtual bool operator> (ColoredCard const & other) const;


};


#endif //CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
