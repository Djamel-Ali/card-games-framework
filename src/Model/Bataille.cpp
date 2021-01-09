#include "Bataille.hpp"
#include "iostream"

void Bataille::createCards() {
    string noms[] = {"Valet", "Dame", "Roi", "As"};
    int valeurs[] = {11, 12, 13, 14};

    for (int i = 2; i < 15; i++) {
        for (int j = 0; j < 4; j++) {
            if (i < 11) {
                deck.addCard(new Card(to_string(i), i, i));
            } else {
                deck.addCard(new Card(noms[j], valeurs[j], i));
            }
        }
    }

    cout << "Cartes batailles crees" << endl;
}


void Bataille::startGame() {
    initGame();
    deck.distributeCards(16, joueurs);
}

void Bataille::playRound(int indexCardToPlay) {
    tapis.insert(tapis.begin(), joueurs.at(actualPlaying)->playCard(0));
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
    if(*tapis.at(0) == *tapis.at(1)){
        cout << "Bataille !" << endl;
        ohBataille = true;

        return -1;
    }

    ohBataille = false;
    return *tapis.at(0) > *tapis.at(1) ? 1 : 0;
}

Bataille::Bataille(const Deck &deck) : Game(deck) {
    ohBataille = false;
    joueurs.push_back(new Player(0, "Djamel", vector<Card *> {}, 0));
    joueurs.push_back(new Player(1, "Yacine", vector<Card *> {}, 0));
}

void Bataille::nextPlayer() {
    actualPlaying++;
    actualPlaying = actualPlaying % (int)joueurs.size();

    if(actualPlaying == 0){
        decideWinner();
    }
}

void Bataille::print(ostream &out) {
    out << "Les Joueurs :" << endl;

    for(Player* player : joueurs){
        out << player-> getName() << " possede " << player->getHand().size() << " cartes" << endl;
    }

    if(! tapis.empty()){
        out << " Le tapis :" << endl;
        out << "la carte de " << joueurs.at(0)-> getName() << " : " << endl;
        for(Card* card : tapis){
            out << *card << endl;
        }
        out << "la carte de " << joueurs.at(1)-> getName() << " : " << endl;
    }


}

void Bataille::decideWinner() {

    int roundWinner = getIndexOfParseCard();

    if(roundWinner != -1){
        cout << "le joueur " << joueurs.at(roundWinner)->getName() << " gagne ce round"<< endl;
    }else{
        cout << "BATAILLE !, les cartes sont remises en jeu " << endl;
    }

    if(!ohBataille){
        while (!tapis.empty()){
            joueurs.at(roundWinner)->addCard(tapis.back());
            tapis.pop_back();
        }
    }

}


