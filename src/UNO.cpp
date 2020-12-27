#include "UNO.hpp"

UNO::UNO(const Deck &deck) : HuitAmericain(deck) {
    colors = new COLOR[5];
    colors[0] = BLEU;
    colors[1] = JAUNE;
    colors[2] = VERT;
    colors[3] = ROUGE;
    colors[4] = NONE;
}

void UNO::createCards() {
    COLOR colors[] = {BLEU, JAUNE, VERT, ROUGE, NONE};

    for (int z = 0; z < 4; z++){
        deck.addCard(new ColoredCard("0", 0, 0, colors[z]));
    }

    // card  1 - 9 , "+2", "passerTour", "sensInverse"
    for (int numero = 1; numero <= 12; numero++){
        for (int x = 0; x < 2; x++){
            for (int color = 0; color < 4; color++){
                deck.addCard(new ColoredCard(to_string(numero), numero, numero, colors[color]));
            }
        }
    }

    // card "changerCouleur", "+4"
    for (int numero = 13; numero <= 14; numero++){
        for (int x = 0; x < 4; x++){
            deck.addCard(new ColoredCard(to_string(numero), numero, 50, colors[4]));
        }
    }
}

void UNO::startGame() {
    initGame();
    deck.distributeCards(7, joueurs);
}

//modifications a faire pour le controller !!
void UNO::playRound(int indexCardToPlay) {
    if(isWinner()){
        getWinner();
        return;
    }

    if(playerCanPlay(joueurs[actualPlaying]->getHand())){
        Card* temp = joueurs[actualPlaying]->playCard(indexCardToPlay);
        if(cardPlayable(temp)){
            deck.addCard(cardOnTop);
            cardOnTop = temp;
            getIndexOfParseCard();

            nextPlayer();
        }
    }else{
        nextPlayer();
    }


}

int UNO::getIndexOfParseCard() {
    switch (cardOnTop->getId()) {
        case 10:
            nextPlayer();
            plusTwo();
            break;
        case 11:
            nextPlayer();
            break;
        case 12:
            reversed();
            break;
        case 13:
            return 1;
        case 14:
            nextPlayer();
            plusFour();
            break;
    }

    return 0;
}
