#include <iostream>
#include "UNO.hpp"

UNO::UNO(const Deck &deck) : Game(deck), sensInverse{false} {
    cout << "\nConstruct UNO\n" << endl;
}

void UNO::initGame() {
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

}

//todo: modifications a faire pour le controller !!
void UNO::playRound(int indexCardToPlay) {
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

int UNO::getIndexOfParseCard() {
    switch (cardOnTop->getId()) {
        case 10:
            // "+2" (le joueur suivant doit piocher 2 cartes et passe son tour)
            nextPlayer();
            plusTwo();
            break;
        case 11:
            // "passerTour" (le joueur suivant doit passer son tour)
            nextPlayer();
            break;
        case 12:
            // "sensInverse"
            reversed();
            break;
        case 13:
            // "changerCouleur" (il peut ou non choisir de changer de couleur en l’annonçant aux autre joueurs)
            return 1;
        case 14:
            // "+4" ( le joueur suivant doit piocher 4 cartes et passer son tour)
            nextPlayer();
            plusFour();
            break;
    }

    return 0;
}

// cherche dans la liste des joueurs actuels s'il y a un gagnant
bool UNO::isWinner() {
    for(Player* player : joueurs){
        if(player->handEmpty()){
            return true;
        }
    }
    return false;
}

// retourne l'index du gagnant dans la liste des joueurs
int UNO::getWinner() {
    for(int i = 0; i < joueurs.size(); i ++){
        if (joueurs.at(i)->handEmpty()){
            return i;
        }
    }
    return -1;
}

void UNO::plusTwo() {
    for(int i = 0; i < 2; i ++){
        joueurs[actualPlaying]->addCard(deck.getCard());
    }
}


void UNO::plusFour(){
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

bool UNO::cardPlayable(Card *toPlay) {
    return cardOnTop == toPlay;
}

