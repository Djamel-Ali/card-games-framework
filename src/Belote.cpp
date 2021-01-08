//
// Created by mdyac on 23/12/2020.
//

#include "Belote.hpp"

Belote::Belote(const Deck &deck) : Game(deck) {
    atout = NONE;
    fold = NONE;
    lastFoldWinner = -1;
    actualPlaying = 0;

}

void Belote::createCards() {
    COLOR colors[] = {PIQUE, CARREAU, TREFLE, COEUR};
    string nom[] = {"7", "8", "9", "10", "VALET", "DAME", "ROI", "AS"};
    int id[] = {7, 8, 9, 10, 11, 12, 13, 14};
    int valeur[] = {0, 0, 0, 10, 2, 3, 4, 11};

    for(int i = 0; i < 8; i++){
        for(auto & color : colors){
            deck.addCard(new ColoredCard(nom[i], id[i], valeur[i], color));
        }
    }
}

void Belote::startGame() {
    initGame();
    deck.distributeCards(5, joueurs);
    deck.distributeCards(3, joueurs);


}

void Belote::playRound(int indexCardToPlay) {
    Card* temp = joueurs[actualPlaying]->getHand().at(indexCardToPlay);

    if(cardPlayable(temp)){
        tapis[actualPlaying] = joueurs[actualPlaying]->playCard(indexCardToPlay);
        if(fold == NONE && lastFoldWinner == -1){
            fold = dynamic_cast<ColoredCard*>(temp)->getColor();
            lastFoldWinner = actualPlaying;
        }else{
            getIndexOfParseCard();

        }
    }
}

bool Belote::isWinner() {
    return false;
}

int Belote::getWinner() {
    return 0;
}

int Belote::getIndexOfParseCard() {
    if(dynamic_cast<ColoredCard*>(tapis[actualPlaying])->getColor() == atout
       && dynamic_cast<ColoredCard*>(tapis[lastFoldWinner])->getColor()!= atout) return actualPlaying;

    if(dynamic_cast<ColoredCard*>(tapis[actualPlaying])->getColor() != atout
       && dynamic_cast<ColoredCard*>(tapis[lastFoldWinner])->getColor()== atout) return lastFoldWinner;

    if(dynamic_cast<ColoredCard*>(tapis[actualPlaying])->getColor() == fold
       && dynamic_cast<ColoredCard*>(tapis[lastFoldWinner])->getColor()!= fold) return actualPlaying;

    if(dynamic_cast<ColoredCard*>(tapis[actualPlaying])->getColor() != fold
       && dynamic_cast<ColoredCard*>(tapis[lastFoldWinner])->getColor() == fold) return lastFoldWinner;




}

// a completer pour false
bool Belote::cardPlayable(Card *toPlay) {

    if(fold == NONE) return true;
    if(fold == dynamic_cast<ColoredCard*>(toPlay)->getColor()) return true;
    if(atout == dynamic_cast<ColoredCard*>(toPlay)->getColor()) return true;

    return true;
}


