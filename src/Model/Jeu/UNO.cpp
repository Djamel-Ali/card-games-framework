#include "UNO.hpp"

UNO::UNO(Deck *_deck) : HuitAmericain(_deck) {
    colors = new COLOR[5];
    colors[0] = BLEU;
    colors[1] = JAUNE;
    colors[2] = VERT;
    colors[3] = ROUGE;
    colors[4] = NONE;
}

void UNO::createCards() {
    COLOR colors[] = {BLEU, JAUNE, VERT, ROUGE, NONE};
    string noms[] = {"+2", "/O", "><", "cC", "+4"};
    for (int z = 0; z < 4; z++){
        deck->addCard(new ColoredCard("0", 0, 0, colors[z]));
    }

    int k = 0;

    // card  1 - 9 , "+2", "passerTour", "sensInverse"
    for (int numero = 1; numero <= 12; numero++){
        for (int x = 0; x < 2; x++){
            for (int color = 0; color < 4; color++){
                if(numero < 10){
                    deck->addCard(new ColoredCard(to_string(numero), numero, numero, colors[color]));
                }else{
                    deck->addCard(new ColoredCard(noms[k], numero, numero, colors[color]));
                }
            }
        }
        if(numero > 9){
            k++;
        }
    }

    // card "changerCouleur", "+4"
    for (int numero = 13; numero <= 14; numero++){
        for (int x = 0; x < 4; x++){
            deck->addCard(new ColoredCard(noms[k], numero, 50, colors[4]));
        }
        k++;
    }

}

/**
 * Vérifie la dernière carte jouée,
 * et fait les actions selon la carte
 * +2, +4, ChangerCouleur, nextPlayer, changerSens
 */

int UNO::getIndexOfParseCard() {
    switch (cardOnTop->getId()) {
        case 10:
            nextPlayer();
            plusTwo();
            break;
        case 11:
            cout << joueurs[actualPlaying]->getName() << " a fait passer le tour du prochain joueur" << endl;
            nextPlayer();
            break;
        case 12:
            reversed();
            break;
        case 13:
            changeColor();
            return 1;
        case 14:
            nextPlayer();
            plusFour();
            break;
    }

    return 0;
}