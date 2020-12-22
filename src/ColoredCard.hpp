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
            out << "BLEU";
            break;
        case VERT:
            out << "VERT";
            break;
        case JAUNE:
            out << "JAUNE";
            break;
        case ROUGE:
            out << "ROUGE";
            break;
        case TREFLE:
            out << "TREFLE";
            break;
        case CARREAU:
            out << "CARREAU";
            break;
        case COEUR:
            out << "COEUR";
            break;
        case PIQUE:
            out << "PIQUE";
            break;
        case NONE:
            out << "NONE";
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

};


#endif //CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
