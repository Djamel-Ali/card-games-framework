#include <iostream>
#include <limits>
#include "HuitAmericain.hpp"

HuitAmericain::HuitAmericain(Deck *_deck) : Game(_deck){
    colors = new COLOR[5];
    colors[0] = TREFLE;
    colors[1] = COEUR;
    colors[2] = CARREAU;
    colors[3] = PIQUE;
    colors[4] = NONE;

    joueurs.push_back(new Player("Djamel", vector<Card *> {}, false,0));
    joueurs.push_back(new Player("Yacine", vector<Card *> {}, true,0));

}

HuitAmericain::~HuitAmericain(){

}

/**
 * Ajoute 2 cartes au joueur suivant, et le fait passer (carte +2)
 */

void HuitAmericain::plusTwo() {
    cout << joueurs[actualPlaying]->getName() << " +2 cartes et passe son tour" << endl;
    for(int i = 0; i < 2; i ++){
        joueurs[actualPlaying]->addCard(deck->getCard());
    }
}

/**
 * Ajoute 4 cartes au joueur suivant, et le fait passer (carte +4)
 */

void HuitAmericain::plusFour(){
    cout << joueurs[actualPlaying]->getName() << " +4 cartes et passe son tour" << endl;
    for(int i = 0; i < 4; i ++){
        joueurs[actualPlaying]->addCard(deck->getCard());
    }
}

/**
 * Change le sens du jeu (carte changerSens)
 */

void HuitAmericain::reversed(){
    cout << joueurs[actualPlaying]->getName() << " a changé le sens du jeu" << endl;
    sensInverse = !sensInverse;
}

/**
 * Change le couleur du jeu (Carte changerColor)
 */

void HuitAmericain::changeColor() {

    cout << "Tu as joué la carte : Changement de Couleur" << endl;
    cout << "#1# pour " << colors[0] << endl;
    cout << "#2# pour " << colors[1] << endl;
    cout << "#3# pour " << colors[2] << endl;
    cout << "#4# pour " << colors[3] << endl;

    int color = -1;

    while (true)
    {
        cin >> color;
        if (!cin || color < 1 || color > 4)
        {
            cout << "Erreur, merci d'entrer une couleur valide " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    }

    switch (color) {
        case 1:
            colors[4] = colors[0];
            break;
        case 2:
            colors[4] = colors[1];
            break;
        case 3:
            colors[4] = colors[2];
            break;
        case 4:
            colors[4] = colors[3];
            break;
        default:
            cout << "Couleur Modifiée";
            break;
    }
}

/**
 * Vérifie si une carte est jouable, selon la couleur, le numéro ou carte Joker
 */

bool HuitAmericain::cardPlayable(Card *toPlay) {
    if((dynamic_cast<ColoredCard*>(tapis[0])->getColor() == NONE && colors[4] != NONE) || dynamic_cast<ColoredCard*>(toPlay)->getColor() == NONE){
        return dynamic_cast<ColoredCard*>(toPlay)->getColor() == colors[4];
    }

    return *dynamic_cast<ColoredCard*>(tapis[0]) == *dynamic_cast<ColoredCard*>(toPlay);
}

/**
 * Vérifie si un joueur possede une carte jouable
 */

bool HuitAmericain::playerCanPlay() {
    for(Card* card : joueurs[actualPlaying]->getHand()){
        if(cardPlayable(card)){
            return true;
        }
    }

    Card * pioche = deck->getCard();
    cout << "carte piochée" << endl;
    cout << "-----------------------------------------" << endl;
    cout << *dynamic_cast<ColoredCard *>(pioche) << endl;


    if(cardPlayable(pioche)){
        cout << "la carte est jouée automatiquement !" << endl;
        deck->addCard(tapis.front());
        tapis.insert(tapis.begin(), pioche);
        nextPlayer();
    }else{
        cout << "dommage la carte est non jouable, elle est ajoutée à ta main " << endl;
        joueurs[actualPlaying]->addCard(pioche);
        passerTour();
    }
    cout << "-----------------------------------------" << endl;


    return false;
}

/**
 * Met a jout les points des joueurs
 */

void HuitAmericain::setPoints(int iPlayer) {
    for(Card* card : joueurs[iPlayer]->getHand()){
        joueurs[iPlayer]->setCurrentScore(joueurs[iPlayer]->getCurrentScore() +card->getValue());
    }
}

void HuitAmericain::createCards() {
    COLOR symbols[] = {TREFLE, COEUR, CARREAU, PIQUE, NONE};

    // cards  3 - 7 (Leur propre valeur numérale)
    for (int numero = 3; numero <= 7; numero++){
        for (int symbol = 0; symbol < 4; symbol++){
            deck->addCard(new ColoredCard(to_string(numero), numero, (float)numero, symbols[symbol]));
        }
    }
    // cards  "9" (leur propre valeur numérale)
    for (int symbol = 0; symbol < 4; symbol++){
        deck->addCard(new ColoredCard(to_string(9), 9,9,symbols[symbol]));
    }

    // cards  "Dame" and "Roi" (value 10 points)
    for (int symbol = 0; symbol < 4; symbol++){
        deck->addCard(new ColoredCard("DAME", 10,10,symbols[symbol]));
        deck->addCard(new ColoredCard("ROI", 11,10,symbols[symbol]));
    }

    // cards  Valet, AS, 2 (value 20 points )
    for (int symbol = 0; symbol < 4; symbol++){
        deck->addCard(new ColoredCard("VALET", 12,20, symbols[symbol]));
        deck->addCard(new ColoredCard("AS", 13,20, symbols[symbol]));
        deck->addCard(new ColoredCard("2", 2,20, symbols[symbol]));
    }

    // cards "8" and "Joker" : (value 50 points )
    // (4 cartes de 8 et 2 cartes de jocker avec NONE comme symbol)
    for (int symbol = 0; symbol < 4; symbol++)
        deck->addCard(new ColoredCard(to_string(8),  8,50, symbols[4]));

    deck->addCard(new ColoredCard("JOKER", 14, 50, symbols[4]));
    deck->addCard(new ColoredCard("JOKER", 14, 50, symbols[4]));
}

// 7 cartes par joueur
void HuitAmericain::distribution() {
    deck->distributeCards(7, joueurs);

    Card * temp = deck->getCard();
    while(dynamic_cast<ColoredCard *>(temp)->getColor() != NONE){
      temp = deck->getCard();
      deck->addCard(temp);
    }
        
    tapis.insert(tapis.begin(), temp);
}

bool HuitAmericain::isWinner() {
    for(Player* player : joueurs){
        if(player->handEmpty()){
            return true;
        }
    }

    return false;
}

int HuitAmericain::getWinner() {
    int winner = -1;
    for(int i = 0; i < (int)joueurs.size(); i ++){
        if (joueurs.at(i)->handEmpty()){
            winner = i;
        }else{
            setPoints(i);
        }
    }

    return winner;
}

/**
 * Vérifie la dernière carte jouée,
 * et fait les actions selon la carte
 * 2, 8, Valet, AS, Joker
 */

int HuitAmericain::getIndexOfParseCard() {
    switch (tapis[0]->getId()) {

        case 2://2
            passerTour();
            plusTwo();
            break;
        case 8: //8
            changeColor();
            return 1;
        case 12://VALET
            passerTour();
            break;
        case 13: //AS
            reversed();
            break;
        case 14://JOKER
            passerTour();
            plusFour();
            changeColor();
            break;
    }

    return 0;
}

/**
 * Passer au joueur suivant
 */

void HuitAmericain::nextPlayer() {
    getIndexOfParseCard();

    actualPlaying = (sensInverse) ? (actualPlaying -1) : (actualPlaying +1);
    if(actualPlaying < 0){
        actualPlaying += (int)joueurs.size();
    }else{
        actualPlaying = actualPlaying % (int)joueurs.size();
    }


    deck->addCard(tapis.back());
}

void HuitAmericain::print(ostream &out) {
    out << "Les Joueurs :" << endl;

    for(Player* player : joueurs){
        out << player-> getName() << " a " << player->getCurrentScore() << " points" << endl;
        out << player-> getName() << " a " << player->getHand().size() << " cartes en main" << endl;
    }

    out << "------------------------------" << endl;

    if((int)tapis.size() > 0){
        out << "Carte au dessus" << endl;
        out << *dynamic_cast<ColoredCard*>(tapis[0]) << endl;

    }

    if(dynamic_cast<ColoredCard*>(tapis[0])->getColor() == NONE && colors[4] != NONE){
        out << "Couleur a jouer : " << endl;
        out << colors[4] << endl;
    }

    out << "------------------------------" << endl;

    if(! isWinner()){
        out << "La main de " << joueurs.at(actualPlaying)->getName() << endl;

        for(Card* card : joueurs.at(actualPlaying)->getHand()){
            out << *dynamic_cast<ColoredCard*>(card) << endl;
        }
    }
}

void HuitAmericain::passerTour() {
    actualPlaying = (sensInverse) ? (actualPlaying -1) : (actualPlaying +1);
    actualPlaying = actualPlaying % (int)joueurs.size();
}
