#include "Bataille.hpp"
#include "iostream"

Bataille::Bataille(Deck *deck) : Game(deck) {
    ohBataille = false;
    joueurs.push_back(new Player(0, "Djamel", vector<Card *> {}, 0));
    joueurs.push_back(new Player(1, "Yacine", vector<Card *> {}, 0));
    std::cout << "Construction of Bataille" << std::endl;
}

void Bataille::createCards() {
    string noms[] = {"Valet", "Dame", "Roi", "As"};
    int valeurs[] = {11, 12, 13, 14};

    for (int i = 2; i < 15; i++) {
        for (int j = 0; j < 4; j++) {
            if (i < 11) {
                Card *temp = new Card(to_string(i), i, i);
                deck->addCard(temp);
            } else {
                Card *temp = new Card(noms[j], i, valeurs[j]);
                deck->addCard(temp);
            }
        }
    }

    cout << "Cartes batailles crees" << endl;
}


void Bataille::startGame() {
    initGame();

}

/**
 * Jouer la 1e carte de la main
 */

void Bataille::playRound(int indexCardToPlay) {
    tapis.insert(tapis.begin(), joueurs.at(actualPlaying)->playCard(0));

    nextPlayer();
}

bool Bataille::isWinner() {
    for (Player *player : joueurs) {
        if (player->handEmpty()) {
            return tapis.empty() || (!tapis.empty() && ohBataille);
        }
    }

    return false;
}

int Bataille::getWinner() {
    if(joueurs.at(0)->handEmpty()){
        joueurs[1]->setCurrentScore(joueurs[1]->getCurrentScore() +1);
        return 1;
    }

    joueurs[0]->setCurrentScore(joueurs[0]->getCurrentScore() +1);
    return 0;
}

/**
 * Verifie le gagnant de la manche ou égalité (ohBataille !)
 */

int Bataille::getIndexOfParseCard() {
    if(*tapis.at(0) == *tapis.at(1)){
        cout << "Bataille !" << endl;
        ohBataille = true;

        return -1;
    }

    ohBataille = false;
    return *tapis.at(0) > *tapis.at(1) ? 1 : 0;
}

/**
 * passe au joueur suivant, affiche le vinqueur s'il y en a un
 */

void Bataille::nextPlayer() {
    actualPlaying++;
    actualPlaying = actualPlaying % (int)joueurs.size();

    if(actualPlaying == 0){
        cout << *this;
        decideWinner();
    }
}

void Bataille::print(ostream &out) {
    out << "Les Joueurs :" << endl;

    for(Player* player : joueurs){
        out << player-> getName() << " possede " << player->getHand().size() << " cartes" << endl;
    }

    if(!tapis.empty()){
        out << "Le tapis :" << endl;
        if(tapis.size() % 2 == 0){
            out << "la carte de " << joueurs.at(1)-> getName() << " : " << endl;
        }else{
            out << "la carte de " << joueurs.at(0)-> getName() << " : " << endl;
        }

        for(Card* card : tapis){
            out << *card << endl;
        }
        if(tapis.size() % 2 == 0){
            out << "la carte de " << joueurs.at(0)-> getName() << " : " << endl;
        }else{
            out << "la carte de " << joueurs.at(1)-> getName() << " : " << endl;
        }

    }


}

void Bataille::decideWinner() {

    int roundWinner = getIndexOfParseCard();

    if(roundWinner != -1){
        cout << "le joueur " << joueurs.at(roundWinner)->getName() << " gagne ce round"<< endl;
    }else{
        cout << "les cartes sont remises en jeu " << endl;
    }

    if(!ohBataille){
        while (!tapis.empty()){
            joueurs.at(roundWinner)->addCard(tapis.back());
            tapis.pop_back();
        }
    }

}

void Bataille::distribution() {
    //deck->distributeCards(1, joueurs);
    joueurs[0]->addCard(new Card("10", 10, 10));
    joueurs[1]->addCard(new Card("10", 10, 10));
    joueurs[1]->addCard(new Card("10", 10, 10));
}


