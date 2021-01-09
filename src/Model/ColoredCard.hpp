#ifndef CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
#define CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP

#include "Card.hpp"
#include <iostream>
enum COLOR {
    BLEU, VERT, JAUNE, ROUGE, TREFLE, COEUR, CARREAU, PIQUE, NONE
};

static std::ostream& operator<<(std::ostream& out, COLOR colo)
{
    switch (colo) {
        case BLEU:
            out << "B";
            break;
        case VERT:
            out << "V";
            break;
        case JAUNE:
            out << "J";
            break;
        case ROUGE:
            out << "R";
            break;
        case TREFLE:
            out << "T";
            break;
        case CARREAU:
            out << "CA";
            break;
        case COEUR:
            out << "CO";
            break;
        case PIQUE:
            out << "P";
            break;
        case NONE:
            out << "N";
            break;
    }

    return out;
}

class ColoredCard : public Card {

private:
    COLOR color;

public:
    ColoredCard(const string &_name, int id, int _value, COLOR _color);

    ~ColoredCard();

    COLOR getColor() const;

    virtual bool operator==(ColoredCard const & other) const;

    friend ostream& operator<<(ostream& out, const ColoredCard &fs);

    friend ostream& operator<<(ostream& out, const COLOR &colo);

    void setValue(int v);
};


#endif //CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
