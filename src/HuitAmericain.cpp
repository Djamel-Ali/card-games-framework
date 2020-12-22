#include "HuitAmericain.hpp"

HuitAmericain::HuitAmericain(const Deck &deck) : Game(deck) {

}

void HuitAmericain::initGame() {
    COLOR colors[] = {PIQUE, COEUR, CARREAU, TREFLE, NONE};
    string noms[] = {"Valet", "Dame", "Roi", "As"};
    int valeurs[] = {20, 3, 4, 5, 6, 7, 50, 9, 10, 11, 12, 13};
                   //  2  3  4  5  6  7   8  9, 20v, 10d, 10r, 20a, 50j
    for (int i = 2; i < 14; i++) {
        for (int j = 0; j < 4; j++) {
            if (i < 10) {
                deck.addCard(new ColoredCard(to_string(i), i, valeurs[i], colors[j]));
            } else {
                deck.addCard(new ColoredCard(noms[j], i, valeurs[i], colors[4]));
            }
        }
    }

    for(int i = 0; i < 4; i++){
        deck.addCard(new ColoredCard("JOKER", 14, 50, colors[i]));
    }

    deck.shuffleCards();
}

void HuitAmericain::distributeCards() {
    for(Player* player : joueurs){
        for(int i = 0; i < 8; i++){
            player->addCard(deck.getCard());
        }
    }
}

void HuitAmericain::startGame() {
    initGame();

}

//modifications a faire pour le controller !!
void HuitAmericain::playRound(int indexCardToPlay) {
    if(isWinner()){
        getWinner();
        return;
    }

    Card* temp = joueurs[actualPlaying]->playCard(indexCardToPlay);
    if(cardPlayable(temp)){
        deck.addCard(cardOnTop);
        cardOnTop = temp;
        getIndexOfParseCard();

        nextPlayer();
    }


}

int HuitAmericain::getIndexOfParseCard() {
    switch (cardOnTop->getId()) {
        case 2://2
            nextPlayer();
            plusTwo();
            break;
        case 10://VALET
            nextPlayer();
            break;
        case 12: //AS
            reversed();
            break;
        case 8: //8
            changeColor();
            return 1;
        case 13://JOKER
            nextPlayer();
            plusFour();
            break;
    }

    return 0;
}

bool HuitAmericain::isWinner() {
    for(Player* player : joueurs){
        if(player->handEmpty()){
            return true;
        }
    }

    return false;
}

int HuitAmericain::getWinner() {
    for(int i = 0; i < joueurs.size(); i ++){
        if (joueurs.at(i)->handEmpty()){
            return i;
        }
    }

    return -1;
}

void HuitAmericain::plusTwo() {
    for(int i = 0; i < 2; i ++){
        joueurs[actualPlaying]->addCard(deck.getCard());
    }
}

void HuitAmericain::plusFour(){
    for(int i = 0; i < 4; i ++){
        joueurs[actualPlaying]->addCard(deck.getCard());
    }
}

void HuitAmericain::reversed(){
    sensInverse = !sensInverse;
}

void HuitAmericain::nextPlayer() {
    actualPlaying = (sensInverse) ? (actualPlaying -1) : (actualPlaying +1);

    if(actualPlaying < 0) actualPlaying = int(joueurs.size()) -1;
    if(actualPlaying >= joueurs.size()) actualPlaying = 0;
}

void HuitAmericain::changeColor() {
    switch (1) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
    }
}

bool HuitAmericain::cardPlayable(Card *toPlay) {

    return cardOnTop == toPlay;
}