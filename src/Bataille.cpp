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

void Bataille::startGame() {

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
    return 0;
}

int Bataille::whichCardWins() {

}
