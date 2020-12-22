#include "Bataille.hpp"
#include "Player.hpp"
#include <algorithm>
#include <random>


void Bataille::createCards() {
    string noms[] = {"Valet", "Dame", "Roi", "As"};
    int valeurs[] = {11, 12, 13, 14};

    for (int i = 2; i < 15; i++) {
        for (int j = 0; j < 4; j++) {
            if (i < 11) {
                deck.addCard(new Card(to_string(i), i, 0));
            } else {
                deck.addCard(new Card(noms[j], valeurs[j], 0));
            }
        }
    }
}


void Bataille::startGame() {
    initGame();
    while(!isWinner()){
        playRound(0);
    }

}

void Bataille::playRound(int indexCardToPlay) {
    for(Player* player : joueurs){
        tapis.insert(tapis.begin(), player->playCard(0));
    }

    int roundWinner = getIndexOfParseCard();
    if(!ohBataille){
        while (!tapis.empty()){
            joueurs.at(roundWinner)->addCard(tapis.back());
            tapis.pop_back();
        }
    }

}

bool Bataille::isWinner() {
    for (Player *player : joueurs) {
        if (player->handEmpty()) {
            return true;
        }
    }

    return false;
}

int Bataille::getWinner() {
    if(joueurs.at(0)->handEmpty()){
        return 0;
    }

    return 1;
}

int Bataille::getIndexOfParseCard() {
    if(tapis.at(0) == tapis.at(1)){
        ohBataille = true;

        return -1;
    }

    ohBataille = false;

    return tapis.at(0) > tapis.at(1) ? 1 : 0;
}


