#include "Bataille.hpp"

void Bataille::initGame() {
    string noms[] = {"Valet", "Dame", "Roi", "As"};
    int valeurs[] = {11, 12, 13, 14};

    for(int i = 2; i < 15; i++){
        for(int j = 0; j < 4; j++){
            if(i < 11){
                deck.addCard(new Card(to_string(i), i, 0));
            }else{
                deck.addCard(new Card(noms[j], valeurs[j], 0));
            }
        }
    }
}

void Bataille::distributeCards() {
    for(int i = 0; i < 16; i++){
        joueurs.at(0).addCard(deck.getCard());
    }
    for(int i = 0; i < 16; i++){
        joueurs.at(1).addCard(deck.getCard());

    }
}

void Bataille::startGame() {
    initGame();
    while(!isWinner()){
        playRound();
    }

}

void Bataille::playRound() {
    for(Player player : joueurs){
        tapis.insert(tapis.begin(), player.playCard());
    }

    int roundWinner = whichCardWins();
    if(!ohBataille){
        while (!tapis.empty()){
            joueurs.at(roundWinner).addCard(tapis.back());
            tapis.pop_back();
        }
    }

}

bool Bataille::isWinner() {
    for(Player player : joueurs){
        if(player.handEmpty()){
            return true;
        }
    }

    return false;
}

int Bataille::getWinner() {
    if(joueurs.at(0).emptyHand()){
        return 0;
    }

    return 1;
}

int Bataille::whichCardWins() {
    if(tapis.at(0) == tapis.at(1)){
        ohBataille = true;

        return -1;
    }

    ohBataille = false;

    return tapis.at(0) > tapis.at(1) ? 1 : 0;
}




Bataille::Bataille() = default;
