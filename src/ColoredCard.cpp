#include "ColoredCard.hpp"
#include <iostream>

ColoredCard::ColoredCard(const string &_name, int id, float _value, COLOR _color) :
        Card((_name), id, _value), color(_color) {}

ColoredCard::~ColoredCard() = default;

COLOR ColoredCard::getColor() const {
    return color;
}

bool ColoredCard::operator==(const ColoredCard &other) const {
    cout << "== de ColoredCard \n";

    return this->getId() == other.getId() || this->color == other.color || other.color == NONE;
}

ostream &operator<<(ostream &out, const ColoredCard &coloredCard) {

    out << coloredCard.getName() << ' ' << coloredCard.getColor();
    // Pour simplifier l'affichage des cartes au joueur, il vaut mieux ne pas afficher id et value.
    //out << coloredCard.getId() << "\n";
    //out << coloredCard.getValue() << "\n";

    return out;
}

ostream &operator<<(ostream &out, const COLOR &colo) {
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



