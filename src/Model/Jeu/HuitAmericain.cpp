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

    joueurs.push_back(new Player("Djamel", vector<Card *> {}, 0));
    joueurs.push_back(new Player("Yacine", vector<Card *> {}, 0));

    cardOnTop = nullptr;
}

HuitAmericain::~HuitAmericain(){
    delete cardOnTop;
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

    cout << "Tu as joué la carte cC : Changement de Couleur" << endl;
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
    if(dynamic_cast<ColoredCard*>(cardOnTop)->getColor() == NONE && colors[4] != NONE){
        return dynamic_cast<ColoredCard*>(toPlay)->getColor() == colors[4];
    }

    return *dynamic_cast<ColoredCard*>(cardOnTop) == *dynamic_cast<ColoredCard*>(toPlay);
}

/**
 * Vérifie si un joueur possede une carte jouable
 */

bool HuitAmericain::playerCanPlay(const vector<Card *>& hand) {
    for(Card* card : hand){
        if(cardPlayable(card)){
            return true;
        }
    }

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
            deck->addCard(new ColoredCard(to_string(numero), numero, numero, symbols[symbol]));
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
    cardOnTop = deck->getCard();
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
    switch (cardOnTop->getId()) {
        case 2://2
            nextPlayer();
            plusTwo();
            break;
        case 8: //8
            changeColor();
            return 1;
        case 10://VALET
            cout << joueurs[actualPlaying]->getName() << " a fait passer le tour du prochain joueur" << endl;
            nextPlayer();
            break;
        case 12: //AS
            reversed();
            break;
        case 13://JOKER
            nextPlayer();
            plusFour();
            changeColor();
            break;
    }

    return 0;
}

/**
 * Vérifie que le joueur possede une carte Jouable,
 * Pioche une nouvelle carte dans le cas contraire qui est
 * ou jouée automatiquement ou ajoutée a la main de ce dernier
 */

void HuitAmericain::playRound(int indexCardToPlay) {
    if(playerCanPlay(joueurs[actualPlaying]->getHand())){
        Card* temp = joueurs[actualPlaying]->playCard(indexCardToPlay);
        if(cardPlayable(temp)){
            deck->addCard(cardOnTop);
            cardOnTop = temp;
            getIndexOfParseCard();

            nextPlayer();
        }else{
            joueurs[actualPlaying]->addCard(temp);
            cout << "La carte ne peut pas etre jouée" << endl;
        }
    }else{
        cout << "Aucune carte a jouer !" << endl;
        cout << "Pioche ..." << endl;
        Card * pioche = deck->getCard();

        cout << *dynamic_cast<ColoredCard *>(pioche) << endl;

        if(cardPlayable(pioche)){
            cout << "la carte est jouée automatiquement !" << endl;
            deck->addCard(cardOnTop);
            cardOnTop = pioche;
        }else{
            cout << "dommage la carte est non jouable, elle est ajoutée à ta main " << endl;
            joueurs[actualPlaying]->addCard(pioche);
        }

        nextPlayer();
    }

}

/**
 * Passer au joueur suivant
 */

void HuitAmericain::nextPlayer() {
    actualPlaying = (sensInverse) ? (actualPlaying -1) : (actualPlaying +1);

    actualPlaying = actualPlaying % (int)joueurs.size();
}

void HuitAmericain::print(ostream &out) {
    out << "Les Joueurs :" << endl;

    for(Player* player : joueurs){
        out << player-> getName() << " a " << player->getCurrentScore() << " points" << endl;
        out << player-> getName() << " a " << player->getHand().size() << " cartes en main" << endl;
    }

    out << "------------------------------" << endl;


    if(cardOnTop != nullptr){
        out << "Carte au dessus" << endl;
        out << *dynamic_cast<ColoredCard*>(cardOnTop) << endl;

    }

    if(dynamic_cast<ColoredCard*>(cardOnTop)->getColor() == NONE && colors[4] != NONE){
        out << "Couleur a jouer : " << endl;
        out << colors[4] << endl;
    }

    out << "------------------------------" << endl;

    if(! isWinner()){
        out << "la main de " << joueurs.at(actualPlaying)->getName() << endl;

        for(Card* card : joueurs.at(actualPlaying)->getHand()){
            out << *dynamic_cast<ColoredCard*>(card) << endl;
        }
    }
}