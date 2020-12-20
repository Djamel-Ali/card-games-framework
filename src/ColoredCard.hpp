#ifndef CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
#define CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP

#include "Card.hpp"

enum COLOR {BLEU, VERT, JAUNE, ROUGE, TREFLE, COEUR, CARREAU, PIQUE};

class ColoredCard : public Card{

private:
    COLOR color;

public:
    ColoredCard(string n, int id, int p, COLOR c);
    ~ColoredCard();

    COLOR getColor() const;
};


#endif //CARD_GAMES_FRAMEWORK_COLOREDCARD_HPP
