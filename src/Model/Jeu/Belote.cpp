#include "Belote.hpp"

Belote::Belote(Deck *_deck) : Game(_deck) {
    atout = NONE;
    fold = NONE;
    lastFoldWinner = -1;

    joueurs.push_back(new Player("Djamel", vector<Card *> {}, 0));
    joueurs.push_back(new Player("Mandela", vector<Card *> {}, 0));
    joueurs.push_back(new Player("Yacine", vector<Card *> {}, 0));
    joueurs.push_back(new Player("Ghandi", vector<Card *> {}, 0));

}

/**
 * Verifie si la carte est jouable
 */

bool Belote::cardPlayable(Card *toPlay) {

    // premiere carte du pli
    if(fold == NONE) return true;

    // si c'est une carte de la meme couleur que le pli
    if(fold == dynamic_cast<ColoredCard *>(toPlay)->getColor()) return true;

    // si le vinqueur du pli est son coéquipier
    if(lastFoldWinner == ((actualPlaying +2) %4)) return true;

    // si le joueur possede une carte de la meme couleur que le pli
    if(playerHaveColor(fold)) return false;

    // si c'est une carte atout
    if(atout == dynamic_cast<ColoredCard*>(toPlay)->getColor()) return true;

    // si il a un atout et qui ne le joue pas - dernier cas
    if(playerHaveColor(atout)) return false;

    return true;
}

/**
 * Vérifie si un joueur possede une Couleur (Carte de la Couleur) dans sa main
 */

bool Belote::playerHaveColor(COLOR color) {
    for(Card * card : joueurs.at(actualPlaying)->getHand()){
        if(dynamic_cast<ColoredCard *>(card)->getColor() == color){
            return true;
        }
    }

    return false;
}

/**
 * Modifie les valeurs des cartes atouts
 */

void Belote::setCardsAtout(){
    for(Card * card : deck->getDeckOfCards()){
        auto * temp = dynamic_cast<ColoredCard *>(card);
        if(temp->getId() == 9 && temp->getColor() == atout){
            cout << "set 9 atout" << endl;
            temp->setValue(14);
        }
        if(temp->getId() == 11 && temp->getColor() == atout){
            cout << "set valet atout"<< endl;
            temp->setValue(20);
        }
    }
}

/**
 * Compte et met à jour les points des équipes (tempScore : points du pli en cours)
 */

void Belote::setPoints() {
    for(Card* &card : tapis){
        tempScore[actualPlaying %2] += card->getValue();
        //remise a zero de la valeur du valet atout
        if(card->getValue() == 20){
            dynamic_cast<ColoredCard *>(card) -> setValue(2);
        }
        //remise a zero de la valeur du 9 atout
        if(card->getValue() == 20){
            dynamic_cast<ColoredCard *>(card) -> setValue(0);
        }
        //remise des cartes jouées dans le deck et melanger
        deck->addCard(card);
        deck->shuffleCards();
        //vider le tapis
        card = nullptr;
    }
}

void Belote::createCards() {
    COLOR colors[] = {PIQUE, CARREAU, TREFLE, COEUR};
    string nom[] = {"7", "8", "9", "10", "VALET", "DAME", "ROI", "AS"};
    int id[] = {7, 8, 9, 10, 11, 12, 13, 14};
    int valeur[] = {0, 0, 0, 10, 2, 3, 4, 11};

    for(int i = 0; i < 8; i++){
        for(auto & color : colors){
            deck->addCard(new ColoredCard(nom[i], id[i], valeur[i], color));
        }
    }
}

// 8 cartes par joueur
void Belote::distribution() {
    actualPlaying = ordreDeJeu;
    setCardsAtout();

    deck->distributeCards(5, joueurs);
    atout = dynamic_cast<ColoredCard*>(deck->getDeckOfCards().at(0))->getColor();
    deck->distributeCards(3, joueurs);
}

bool Belote::isWinner() {
    if(joueurs.at(0)->getCurrentScore() > 500){
        return true;
    }else{
        return joueurs.at(1)->getCurrentScore() > 500;
    }
}

int Belote::getWinner() {
    if(joueurs.at(0)->getCurrentScore() > 500){
        return 0;
    }

    return 1;
}

/**
 * Verifie le gagnant du pli
 */

int Belote::getIndexOfParseCard() {

    // si la carte jouée est un atout et que la plus forte du tapis ne l'est pas
    if(dynamic_cast<ColoredCard*>(tapis[actualPlaying])->getColor() == atout
       && dynamic_cast<ColoredCard*>(tapis[lastFoldWinner])->getColor()!= atout) return actualPlaying;

    // si la carte jouée n'est pas un atout et que la plus forte du tapis l'est
    if(dynamic_cast<ColoredCard*>(tapis[actualPlaying])->getColor() != atout
       && dynamic_cast<ColoredCard*>(tapis[lastFoldWinner])->getColor()== atout) return lastFoldWinner;

    // si la carte jouée est de la couleur du pli et que la plus forte du tapis ne l'est pas
    if(dynamic_cast<ColoredCard*>(tapis[actualPlaying])->getColor() == fold
       && dynamic_cast<ColoredCard*>(tapis[lastFoldWinner])->getColor()!= fold) return actualPlaying;

    // si la carte jouée n'est pas de la couleur du pli et que la plus forte du tapis l'est
    if(dynamic_cast<ColoredCard*>(tapis[actualPlaying])->getColor() != fold
       && dynamic_cast<ColoredCard*>(tapis[lastFoldWinner])->getColor() == fold) return lastFoldWinner;

    // derniers choix - on compare les valeurs des deux cartes
    if(dynamic_cast<ColoredCard *>(tapis[actualPlaying])->getId() > dynamic_cast<ColoredCard *>(tapis[lastFoldWinner])->getId()) return actualPlaying;

    return lastFoldWinner;
}

void Belote::playRound(int indexCardToPlay) {
    Card* temp = joueurs[actualPlaying]->getHand().at(indexCardToPlay);

    if(cardPlayable(temp)){
        tapis[actualPlaying] = joueurs[actualPlaying]->playCard(indexCardToPlay);
        if(fold == NONE && lastFoldWinner == -1){
            fold = dynamic_cast<ColoredCard*>(temp)->getColor();
            lastFoldWinner = actualPlaying;
        }else{
            lastFoldWinner = getIndexOfParseCard();
        }

        nextPlayer();
    }else{
        cout << "La carte ne peut pas etre jouée" << endl;
    }
}

/**
 * passe au joueur suivant, met a jour le score et une nouvelle partie si le round est terminé
 */

void Belote::nextPlayer() {
    actualPlaying++;
    actualPlaying = actualPlaying % (int)joueurs.size();

    //test fin du pli (tour de table)
    for(auto & card : tapis){
        if(card == nullptr) return;
    }
    // couleur du pli
    fold = NONE;
    // le vinqueur du pli commence le suivant
    actualPlaying = lastFoldWinner;
    //mise a jour des points du pli
    setPoints();

    //test fin du round (8 plis)
    if(joueurs[actualPlaying]->handEmpty()){
        // si l'équipe qui a pris la main remporte son contrat (faire minimum 81 points) elle gagne 161 points et l'équipe adverse les points des plis gagnés
        if(tempScore[ordreDeJeu %2] > 80){
            joueurs[ordreDeJeu %2]->setCurrentScore(joueurs[ordreDeJeu %2]->getCurrentScore() + 161);
            joueurs[(ordreDeJeu +1) %2]->setCurrentScore(joueurs[(ordreDeJeu +1) %2]->getCurrentScore() +tempScore[(ordreDeJeu +1) %2]);
        }else{// sinon elle est "dedans"
            joueurs[ordreDeJeu %2]->setCurrentScore(joueurs[ordreDeJeu %2]->getCurrentScore() +tempScore[ordreDeJeu %2]);
            joueurs[(ordreDeJeu +1) %2]->setCurrentScore(joueurs[(ordreDeJeu +1) %2]->getCurrentScore() + 161);
        }

        tempScore[0] = 0;
        tempScore[1] = 0;

        ordreDeJeu ++;
        ordreDeJeu = ordreDeJeu %4;

        //round suivant tant qu'aucune équipe n'a fait 500 points
        if(!isWinner()){
            startGame();
        }
    }
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
        out << " -- " ;
    }
    out << endl;
}