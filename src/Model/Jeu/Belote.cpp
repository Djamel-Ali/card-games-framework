#include "Belote.hpp"

Belote::Belote(Deck *_deck) : Game(_deck) {
    atout = PIQUE;
    fold = NONE;
    lastFoldWinner = -1;

    joueurs.push_back(new Player(0, "Djamel", vector<Card *> {}, 0));
    joueurs.push_back(new Player(1, "Mandela", vector<Card *> {}, 0));
    joueurs.push_back(new Player(2, "Yacine", vector<Card *> {}, 0));
    joueurs.push_back(new Player(3, "Ghandi", vector<Card *> {}, 0));

    std::cout << "Construction of Belote" << std::endl;
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
            lastFoldWinner = getIndexOfParseCard();
        }

        nextPlayer();
    }else{
        cout << "La carte ne peut pas etre jouée" << endl;
    }
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
 * passe au joueur suivant, met a jour le score et une nouvelle partie si le round est terminé
 */

void Belote::nextPlayer() {
    actualPlaying++;
    actualPlaying = actualPlaying % (int)joueurs.size();

    for(auto & card : tapis){
        if(card == nullptr) return;
    }

    actualPlaying = lastFoldWinner;

    setPoints();

    if(joueurs[actualPlaying]->handEmpty()){
        if(!isWinner()){
            if(tempScore[ordreDeJeu %2] > 80){
                joueurs[ordreDeJeu %2]->setCurrentScore(joueurs[ordreDeJeu %2]->getCurrentScore() + 161);
                joueurs[(ordreDeJeu +1) %2]->setCurrentScore(joueurs[(ordreDeJeu +1) %2]->getCurrentScore() +tempScore[(ordreDeJeu +1) %2]);
            }else{
                joueurs[ordreDeJeu %2]->setCurrentScore(joueurs[ordreDeJeu %2]->getCurrentScore() +tempScore[ordreDeJeu %2]);
                joueurs[(ordreDeJeu +1) %2]->setCurrentScore(joueurs[(ordreDeJeu +1) %2]->getCurrentScore() + 161);
            }

            tempScore[0] = 0;
            tempScore[1] = 0;

            ordreDeJeu ++;
            ordreDeJeu = ordreDeJeu %4;

            startGame();
        }
    }
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
        ColoredCard * temp = dynamic_cast<ColoredCard *>(card);
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
        if(card->getValue() == 20){
            dynamic_cast<ColoredCard *>(card) -> setValue(2);
        }
        if(card->getValue() == 20){
            dynamic_cast<ColoredCard *>(card) -> setValue(0);
        }
        deck->addCard(card);
        card = nullptr;
    }
}

void Belote::distribution() {
    setCardsAtout();

    deck->distributeCards(5, joueurs);
    deck->distributeCards(3, joueurs);
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