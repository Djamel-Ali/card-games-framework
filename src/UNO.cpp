#include "UNO.hpp"

UNO::UNO(const Deck &deck) : Game(deck) {

}

void UNO::initGame() {
    COLOR colors[] = {BLEU, JAUNE, VERT, ROUGE, NONE};

    for (int z = 0; z < 4; z++){
        deck.addCard(new ColoredCard("0", 0, 0, colors[z]));
    }

    // card rank 1 till 9 , "+2", "passerTour", "sensInverse"
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
            deck.addCard(new ColoredCard(to_string(numero), numero, 0, colors[4]));
        }
    }

    deck.shuffleCards();
}

void UNO::distributeCards() {
    for(Player* player : joueurs){
        for(int i = 0; i < 8; i++){
            player->addCard(deck.getCard());
        }
    }
}

void UNO::startGame() {
    initGame();

    while(!isWinner()){
        playRound();
    }
}

void UNO::playRound() {
    cardOnTop = joueurs[actualPlaying]->playCard();
}


int UNO::whichCardWins() {
    return 0;
}


bool UNO::isWinner() {
    for(Player* player : joueurs){
        if(player->handEmpty()){
            return true;
        }
    }

    return false;
}

int UNO::getWinner() {
    for(int i = 0; i < joueurs.size(); i ++){
        if (joueurs.at(i)->handEmpty()){
            return i;
        }
    }

    return -1;
}





void UNO::plusTwo(int playerIndex) {
    for(int i = 0; i < 2; i ++){
        joueurs[actualPlaying]->addCard(deck.getCard());
    }
}


void UNO::plusFour(int playerIndex){
    for(int i = 0; i < 4; i ++){
        joueurs[actualPlaying]->addCard(deck.getCard());
    }
}

void UNO::reversed(){
    sensInverse = !sensInverse;
}

void UNO::nextPlayer() {
    actualPlaying = (sensInverse) ? (actualPlaying -1) : (actualPlaying +1);

    if(actualPlaying < 0) actualPlaying = int(joueurs.size()) -1;
    if(actualPlaying >= joueurs.size()) actualPlaying = 0;
}

void UNO::changeColor() {

}

bool UNO::cardPlayable(Card *toPlay) {
    return cardOnTop == toPlay;
}

