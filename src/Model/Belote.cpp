//
// Created by mdyac on 23/12/2020.
//

#include "Belote.hpp"

Belote::Belote(const Deck &deck) : Game(deck) {
    atout = NONE;
    fold = NONE;
    lastFoldWinner = -1;
    actualPlaying = 0;

    joueurs.push_back(new Player(0, "Djamel", vector<Card *> {}, 0));
    joueurs.push_back(new Player(1, "Mandela", vector<Card *> {}, 0));
    joueurs.push_back(new Player(2, "Yacine", vector<Card *> {}, 0));
    joueurs.push_back(new Player(3, "Ghandi", vector<Card *> {}, 0));

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
    distribution();
    actualPlaying = ordreDeJeu;
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

        nextPlayer();
    }
}

bool Belote::isWinner() {
    if(joueurs.at(0)->getCurrentScore() > pointsMax){
        return true;
    }else{
        return joueurs.at(1)->getCurrentScore() > pointsMax;
    }
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

    if(dynamic_cast<ColoredCard *>(tapis[actualPlaying])->getId() > dynamic_cast<ColoredCard *>(tapis[lastFoldWinner])->getId()) lastFoldWinner = actualPlaying;

    return 1;
}


bool Belote::cardPlayable(Card *toPlay) {

    if(fold == NONE) return true;
    if(fold == dynamic_cast<ColoredCard *>(toPlay)->getColor()) return true;
    if(lastFoldWinner == ((actualPlaying +2) %4)) return true;
    if(playerHaveColor(fold)) return false;
    if(atout == dynamic_cast<ColoredCard*>(toPlay)->getColor()) return true;
    if(playerHaveColor(atout)) return false;

    return true;
}



void Belote::nextPlayer() {
    actualPlaying++;
    actualPlaying = actualPlaying % (int)joueurs.size();

    for(auto & card : tapis){
        if(card == nullptr) return;
    }

    setPoints();

    if(joueurs[actualPlaying]->handEmpty()){
        if(!isWinner()){
            startGame();

            joueurs[0]->setCurrentScore(tempScore[0]);
            joueurs[1]->setCurrentScore(tempScore[1]);
            tempScore[0] = 0;
            tempScore[1] = 0;

            ordreDeJeu ++;
            ordreDeJeu = ordreDeJeu %4;
        }
    }
}

bool Belote::playerHaveColor(COLOR color) {
    for(Card * card : joueurs.at(actualPlaying)->getHand()){
        if(dynamic_cast<ColoredCard *>(card)->getColor() == color){
            return true;
        }
    }

    return false;
}

void Belote::setCardsAtout(){
    for(Card * card : deck.getDeckOfCards()){
        auto * temp = dynamic_cast<ColoredCard *>(card);
        if(temp->getId() == 9 && temp->getColor() == atout){
            temp->setValue(14);
        }
        if(temp->getId() == 11 && temp->getColor() == atout){
            temp->setValue(20);
        }
    }
}

void Belote::setPoints() {
    for(auto &card : tapis){
        tempScore[actualPlaying %4] += card->getValue();
        if(card->getValue() == 20){
            dynamic_cast<ColoredCard *>(card) -> setValue(2);
        }
        if(card->getValue() == 20){
            dynamic_cast<ColoredCard *>(card) -> setValue(0);
        }
        deck.addCard(card);
        card = nullptr;
    }
}

void Belote::distribution() {
    deck.distributeCards(5, joueurs);
    deck.distributeCards(3, joueurs);

    setCardsAtout();
}

void Belote::print(ostream &out) {
    out << "score Round: " << endl;
    out << "Equipe 1 : " << tempScore[0] << endl;
    out << "Equipe 2 : " << tempScore[0] << endl;

    out << "------------------------------" << endl;

    out << "score Partie: " << endl;
    out << "Equipe 1 : " << joueurs[0]->getCurrentScore() << endl;
    out << "Equipe 2 : " << joueurs[1]->getCurrentScore() << endl;

    out << "------------------------------" << endl;

    out << "Le tapis :" << endl;
    for(Card * card : tapis){
        if(card != nullptr){
            out << *dynamic_cast<ColoredCard *>(card);
        }
    }

    out << "------------------------------" << endl;

    out << "Atout du round :" << endl;
    out << atout << endl;

    out << "------------------------------" << endl;

    out << "joueur en cours : " << endl;
    out << joueurs[actualPlaying]->getName() << endl;
    out << "sa main : " << endl;
    for(Card* card : joueurs.at(actualPlaying)->getHand()){
        out << *dynamic_cast<ColoredCard*>(card);
    }
}