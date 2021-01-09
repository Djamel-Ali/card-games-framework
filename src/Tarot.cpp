#include <iostream>
#include "Tarot.hpp"
#include <algorithm>

Tarot::Tarot(const Deck &deck) : Game(deck), name("TAROT"),
                                 id_of_attacker{-1}, strategy_of_attacker{-1}, goal_of_the_attacker{56},
                                 coefficient_contrat{1}, gagnantDuPli{getAttacker()}{
    cout << "\n\tConstruct Tarot\n" << endl;
}

void Tarot::createCards() {
    COLOR symbols[] = {TREFLE, COEUR, CARREAU, PIQUE, NONE};


    /// N.B: LES NON-ATOUTS SONT DE TYPE ColoredCard
    // [1..10] * 4 = 40 cartes basses (ou blanches) valent chacune 0,5 point (soit un total de 20 points) ;
    for (int numero = 1; numero <= 10; numero++) {
        for (int symbol = 0; symbol < 4; symbol++) {
            deck.addCard(new ColoredCard(to_string(numero), numero, 0.5, symbols[symbol]));
        }
    }

    /// N.B: LES ATOUTS SONT DE TYPE Card
    // [2..20] = 19 atouts du n°2 au n°20 valent chacun 0,5 point (soit un total de 9,5 points) ;
    for (int numero = 2; numero <= 20; numero++) {
        deck.addCard(new Card(to_string(numero), numero, 0.5));
    }

    // les 4 Valets valent chacun 1,5 point (soit un total de 6 points) ;
    // les 4 Cavaliers valent chacun 2,5 points (soit un total de 10 points) ;
    // les 4 Dames valent chacune 3,5 points (soit un total de 14 points) ;
    // les 4 Rois valent chacun 4,5 points (soit un total de 18 points) ;
    for (int symbol = 0; symbol < 4; symbol++) {
        deck.addCard(new ColoredCard("VALET", 11, 1.5, symbols[symbol]));
        deck.addCard(new ColoredCard("CAVALIER", 12, 2.5, symbols[symbol]));
        deck.addCard(new ColoredCard("DAME", 13, 3.5, symbols[symbol]));
        deck.addCard(new ColoredCard("ROI", 14, 4.5, symbols[symbol]));
    }

    // les 3 Bouts valent chacun 4,5 points (soit un total de 13,5 points) ;
    // (les cartes 1 et 21 d'atout + l'EXCUSE)
    for (int numero = 1; numero <= 21; numero += 20) {
        deck.addCard(new Card(to_string(numero), numero, 4.5));
    }
    // la carte 22 d'atout (l'EXCUSE)
    deck.addCard(new Card("EXCUSE", 22, 4.5));

}

void Tarot::startGame() {
    initGame();
    deck.distributeCards(18, joueurs);

    // 6 cartes restantes dans le talon (ou le chien)
    setChien(deck.getDeckOfCards());
    deck.getDeckOfCards().clear();

    // Launch the announcement phase
    launchAnnouncementPhase();
    // À la sortie de cette methode (phase des annonces) on saurait qui est le meneur et qui sont les défenseurs
}

// Other methods :

// Phase dont laquelle un des joueurs décide de jouer le role de l'attaquant
void Tarot::launchAnnouncementPhase() {
    int choice = -1;
    while (id_of_attacker == -1) {
        for (Player *pPlayer : joueurs) {
            pPlayer->displayHand();

            cout << "\n\t1 : Passe \n\t2 : PETITE \n\t3 : GARDE \n\t4 : GARDE SANS CHIEN \n\t5 : GARDE CONTRE CHIEN"
                 << endl;
            cout << "Veuillez saisir le numéro correspondant à votre choix : " << endl;
            cin >> choice;
            switch (choice) {
                case 1 : // passe
                    continue;
                case 2 : // PETITE
                    id_of_attacker = pPlayer->getUniqueId();

                    // L'attaquant (ou le preneur) de la donne courante,
                    // joue la toute première carte de la cette donne,
                    // (aussi il faut initialiser le gagnant du pli par l'attaquant courant car
                    // c'est le gagant du pli courant qui débutera le pli suivant)
                    setGagnantDuPli(getAttacker());

                    strategy_of_attacker = PETITE;
                    cout << "Type de contrat : PETITE --> l'attaquant montre les cartes du chien à ses partenaires :\n";
                    displayChien();

                    // Sur ce contrat (PETITE) les cartes du chien seront intégrées dans la main du preneur, ensuite
                    // le preneur doit écarter 6 cartes de son choix de sa main (qui contient actuellement 24 cartes)
                    integrateThenDiscard();
                    // Les 6 cartes récemment écartées (mises dans Chien) vont rester secrètes tout au long de la partie
                    break;
                case 3 : // GARDE
                    id_of_attacker = pPlayer->getUniqueId();
                    setGagnantDuPli(getAttacker());
                    strategy_of_attacker = GARDE;

                    //Coefficients des différents contrats :  PETITE = 1, GARDE = 2, GARDE SANS CHIEN = 4, GARDE CONTRE CHIEN = 6
                    coefficient_contrat = 2;

                    cout << "Type de contrat : GARDE --> l'attaquant montre les cartes du chien à ses partenaires :\n";
                    displayChien();

                    // Sur ce contrat (GARDE) les cartes du chien seront intégrées dans la main du preneur, ensuite
                    // le preneur doit écarter 6 cartes de son choix de sa main (qui contient actuellement 24 cartes)
                    integrateThenDiscard();
                    // Les 6 cartes récemment écartées (mises dans Chien) vont rester secrètes tout au long de la partie
                    break;
                case 4 : // GARDE SANS CHIEN
                    id_of_attacker = pPlayer->getUniqueId();
                    setGagnantDuPli(getAttacker());
                    strategy_of_attacker = GARDE_SANS_CHIEN;

                    //Coefficients des différents contrats :  
                    //PETITE = 1, GARDE = 2, GARDE SANS CHIEN = 4, GARDE CONTRE CHIEN = 6
                    coefficient_contrat = 4;
                    break;
                case 5 : // GARDE CONTRE CHIEN
                    id_of_attacker = pPlayer->getUniqueId();
                    setGagnantDuPli(getAttacker());
                    strategy_of_attacker = GARDE_CONTRE_CHIEN;

                    //Coefficients des différents contrats :  
                    //PETITE = 1, GARDE = 2, GARDE SANS CHIEN = 4, GARDE CONTRE CHIEN = 6
                    coefficient_contrat = 6;
                    break;
                default:
                    // On sort de switch (et puis de la boucle 'for'), on mélange les cartes,on redistribue
                    // et on recommence jusqu'à ce qu'on trouve un attaquant.
                    cout << "\n\n\tMélange et redistribution\n";
                    break;
            }
        }
        // Si personne ne s'est présenté comme preneur (attaquant) tout le monde remet ses cartes au Deck,
        // on mélange, on redistribue, puis on recommence et ainsi de suite jusqu'à ce ce qu'on trouve un attaquant
        if (id_of_attacker == -1) {
            collectAllTheCards();
            deck.shuffleCards();
            deck.distributeCards(18, joueurs);
        }
    }
    //
}

void Tarot::displayChien() {
    cout << "Chien : ";
    for (Card *pCard : chien) {
        cout << *pCard << " ; ";
    }
}

// Ajouter les cartes du chien à la main de l'attaquant
void Tarot::integrateChien() {
    getAttacker()->getHand().insert
            (getAttacker()->getHand().end(), chien.begin(), chien.end());
    chien.clear();
}

// L'attaquant choisit les 6 cartes à écarter de sa main qui en contient actuellement 24
// (pour les remettre au Chien)
bool Tarot::discardAdditionalCards() {
    int indexOfCardToBeDiscarded = -1;
    bool done = false;
    for (auto i = 6; i > 0; i--) {
        do {
            getAttacker()->displayHand();
            cout << "\n\t" << i << " carte(s) à écarter : " << endl;
            cout << "\tSaisissez l'indice de la carte à écarter svp : ";
            cin >> indexOfCardToBeDiscarded;
            done = moveCardFromTo(getAttacker()->getHand(), chien, indexOfCardToBeDiscarded);
        } while (!done);
    }
    return done;
}

bool Tarot::moveCardFromTo(vector<Card *> &srcVectOfCards, vector<Card *> &targetVectOfCards, int indexOfCard) {
    Card *pCard = srcVectOfCards.at(indexOfCard);
    if(pCard != nullptr){
        targetVectOfCards.push_back(pCard);
        srcVectOfCards.erase(srcVectOfCards.begin() + indexOfCard);
        return true;
    }
    return false;
}

// ajoute les carte du chien à la main du preneur, puis laisse ce dernier choisir les 6 cartes à écarter
void Tarot::integrateThenDiscard() {
    integrateChien();
    discardAdditionalCards();
}


// Returns 'true' when you reach the end of the gameplay ( i.e. When someone reaches or exceeds
// (GAMEPLAY OBJECTIVE) the number of points  set at the beginning of the game
// And that none of the players have any cards in their hands (checks that all Hands Are Empty)).
bool Tarot::isWinner() {
    return someoneAchievedGoal() && endOfDonne();
}

// Returns the winner's ID
int Tarot::getWinner() {
    for (Player *player : joueurs) {
        if (player->getFinalScore() >= GAMEPLAY_OBJECTIVE)
            return player->getUniqueId();
    }
    return -1;
}

// Returns 'true' when you reach the end of the donne (une partie de jeu se compose de plusieures donnes) .
//checks that all Hands Are Empty
bool Tarot::endOfDonne() {
    //If a person still has cards in his or her hands, the game continues.
    for (Player *player : joueurs) {
        if (!player->handEmpty())
            return false;
    }
    return true;
}

//
//int Tarot::getIndexOfParseCard() {
//    return 0;
//}


//L'attaquant (de la donne courante) joue toujours en premier pour débuter la partie,
//Le gagant du pli courant débutera le pli suivant (et puis dans le sens aiguilles d'une montre)
void Tarot::playRound(int indexCardToPlay) {
    // si fin de partie (qqn a atteint le nombre de points objectif)
    if (isWinner()) {
        displayFinalResults();
        return;
    }
    // Car une partie de Tarot se compose de (une ou) plusieurs donnes
    else if (endOfDonne() && !someoneAchievedGoal()) {
        updatesScores();
        collectAllTheCards();
        deck.shuffleCards();
        deck.distributeCards(18, joueurs);

        // 6 cartes restantes dans le talon (ou le chien)
        setChien(deck.getDeckOfCards());
        deck.getDeckOfCards().clear();

        // Launch the announcement phase
        launchAnnouncementPhase();
        // À la sortie de cette methode (phase des annonces) on saurait qui est le meneur et qui sont
        // les défenseurs pour la donne qui suit
    }

    //L'attaquant joue toujours en premier à la première donne,
    // sinon par le gagnant du pli à chaque à chaque fois pour toutes les autres donnes
    // (pour ça le gagnant du pli est initialisé au départ par le preneur)
    int indexOfCardToPlay = getGagnantDuPli()->getIndexOfCardToPlay();
    tapis.insert(tapis.begin(), getAttacker()->playCard(indexOfCardToPlay));


    // Les (3) autres joueurs joueront après lui (le gagnant du pli précédent), un par un.
    makeTheOthersPlay();

    // À la sortie de cette méthode, on aurait mis à jour le gagnantDuPli
    // (donc on calcule la somme des points qu'il vient de gagner sur ce pli)
    gagnantDuPli->setCurrentScore(gagnantDuPli->getCurrentScore()+getSumOfPointsInTapis());

    // Récupération des carte du tapis et on les remet directement dans le deck
    // (car le score est mis à jour au fur et à mesure)
    deck.getDeckOfCards().insert(deck.getDeckOfCards().end(), tapis.begin(), tapis.end());
    tapis.clear();
}

// update (current and final) scores of all players (attacker and defenders)
// (j'affiche en même temps les résultats mis à jour dans cette fonction)
void Tarot::updatesScores() {
    float difference = getAttacker()->getCurrentScore() - (float)goal_of_the_attacker;

    // Le contrat de base vaut 25 points.
    float newGain = (25 + abs(difference)) * (float)coefficient_contrat;

    // Si l'attanquant réalise son contrat (ou son enchère)
    if (difference >= 0) {
        cout << "L'attaquant a réalisé sont contrat" << endl;
        cout << "\n\tL'attaquant : + " << newGain * 3 << " pts." << endl;
        cout << "\tLes défenseurs : " << (-1) * newGain << " pts chacun.";

        // + 3 * newGain pour l'attaquant car on met ((-1) * newGain) à chaque défenseur,
        // (et aussi il faut bien vérier que l'équation : total des points des 4 joueurs == 0
        getAttacker()->setFinalScore(getAttacker()->getFinalScore() + 3 * newGain);
        updateDefendersScores((-1) * newGain);
    } else {
        cout << "L'attaquant n'a pas réussi à réaliser son contrat !" << endl;
        cout << "\n\tL'attaquant :  " << newGain * (-3) << " pts." << endl;
        cout << "\tLes défenseurs : + " << newGain << " pts chacun.";

        getAttacker()->setFinalScore(getAttacker()->getFinalScore() - 3 * newGain);
        updateDefendersScores(newGain);
    }
    displayCalculationSummary();
    getAttacker()->setCurrentScore(0);
}

// mise à jour des scores (finaux et intermediaires) des défenseurs de la donne courante
void Tarot::updateDefendersScores(float newGain) {
    for (Player *player: joueurs) {
        if (player->getUniqueId() != id_of_attacker) {
            player->setFinalScore(player->getFinalScore() + newGain);
            player->setCurrentScore(0);
        }
    }
}

// Display the final scores of the other players (other than the attacker of the deal that just finished).
void Tarot::displayDefendersFinalScores() {
    for (Player *player : joueurs) {
        if (player->getUniqueId() != id_of_attacker) {
            cout << "\n score : " << player->getFinalScore()
            << "( id : " << player->getUniqueId() << " ; Name : " << player->getName()
            << " ; Current status : Defender)" << endl;
        }
    }
}

void Tarot::displayFinalResults() {
    for (Player *player : joueurs) {
        cout << *player;
    }
}

// Affiche les résultats intermédiaires
void Tarot::displayIntermediateResults() {
    for (Player *player : joueurs) {
        cout << "\n\tNom : " << player->getName() << " (id = " << player->getUniqueId() << ")"
             << " =======> Score intermédiaire : " << player->getCurrentScore() << endl;
    }
}

// Affiche les résultats intermediaires avec des explications détatillées du comptage de points
void Tarot::displayCalculationSummary() {
    float difference = getAttacker()->getCurrentScore() - (float)goal_of_the_attacker;

    // Le contrat de base vaut 25 points.
    float newGain = (25 + abs(difference)) * (float)coefficient_contrat;

    cout << "\nExplications \n " << endl;
    cout << "score objectif de l'attaquant <" << getAttacker()->getName() << "> :  " << goal_of_the_attacker << endl;
    cout << "score réalisé : " << getAttacker()->getCurrentScore() << endl;
    cout << "différence : " << difference << endl;
    cout << difference << " pts == (Score réalisé : " << getAttacker()->getCurrentScore()
         << ") - (Score objectif de la donne : " << goal_of_the_attacker << ")\n";

    cout << "( 25 (contrat de base) + " << abs(difference) << " (abs(difference)) ) * " << coefficient_contrat
         << " (coefficient du contrat) " << " == " << newGain << " pts." << endl;

    cout << "score final de l'attaquant: " << getAttacker()->getFinalScore()
         << " ( id de l'attaquant : " << id_of_attacker << " )" << endl;
    cout << "scores finaux des défenseurs: " << endl;
    displayDefendersFinalScores();
}

// récupération de toutes les cartes (mains des joueurs et leurs réserves (cartes gagnées) + Le Chien)
// pour les mettre dans Deck
void Tarot::collectAllTheCards() {
    // Récupération des cartes des joueurs
    for (Player *player : joueurs)
    {
        player->putBackHand(deck.getDeckOfCards());
    }
    // Récupération des carte du chien et on met tout dans deck
    deck.getDeckOfCards().insert(deck.getDeckOfCards().end(), chien.begin(), chien.end());
    chien.clear();
}

// Returns 'true' when One of the players won (i.e. it reaches or exceeds the target number of points).
bool Tarot::someoneAchievedGoal() {
    for (Player *player : joueurs) {
        if (player->getFinalScore() >= GAMEPLAY_OBJECTIVE)
            return true;
    }
    return false;
}

// Faire jouer les 3 autres joueurs après le que le gagnant du pli précédent ait joué
void Tarot::makeTheOthersPlay() {
    for(auto i = 0; i < joueurs.size(); i++){
        if(joueurs.at(i)->getUniqueId() != getGagnantDuPli()->getUniqueId()){
            int indexOfCardToPlay = joueurs.at(i)->getIndexOfCardToPlay();

            //todo : vérifier bien qu'il a choisi l'indice d'une carte jouable, sinon (si une carte non attendu)
            // vérifier qu'il n'a vraiment pas le choix (autorisé dans ce cas). ou bien faire une liste des indices des
            // cartes pouvant êtres jouées, et vérifier à chaque fois si la carte choisie en fait partie
            tapis.insert(tapis.begin(), joueurs.at(i)->playCard(indexOfCardToPlay));
        }
    }
    // Les 3 autres joueurs viennent de jouer chacun sa carte

    // Mettre à jour le joueur qui va gagner le pli courant
    // D'abord trouver le joueur qui a posé la carte la plus forte
    // (c'est lui le gagnant du pli, donc on doit mettre à jour cette variable)
    int strongestCardIndex = getStrongestCardIndex(tapis);
    switch (strongestCardIndex) {
        case 0://C'est le 4ème joueur de ce pli qui gagne le pli courant
            gagnantDuPli = get_ith_player(4);
            break;
        case 1://C'est le 3ème joueur de ce pli qui gagne le pli courant
            gagnantDuPli = get_ith_player(3);
            break;
        case 2://C'est le 2ème joueur de ce pli qui gagne le pli courant
            gagnantDuPli = get_ith_player(2);
            break;
        case 3:// C'est le 1er (le même gagant du pli précédent) qui emportera le pli courant
               // (donc gagnantDuPli est déjà à jour)
            break;
        default:
            throw std::runtime_error("\n\tindice de la carte la plus forte est différente des valeurs {0, 1, 2, 3}");
    }
    // À la sortie de tous ces cas, on sait qui vient de gagner le pli (gagnantDuPli mis à jour)
    // (donc on doit mettre à jour son score juste après l'invocation de cette méthode)
}

Player *Tarot::getGagnantDuPli() const {
    return gagnantDuPli;
}

void Tarot::setGagnantDuPli(Player *_gagnantDuPli) {
    Tarot::gagnantDuPli = _gagnantDuPli;
}

int Tarot::getStrongestCardIndex(const vector<Card *> &listOfCards) {
    if(listOfCards.empty())
        throw std::runtime_error("La liste passée en argument est vide !");
    else{
        auto max = listOfCards.at(0)->getId();
        auto indexOfMax = 0;
        for(auto i = 1; i < listOfCards.size(); i++){
            if(max < listOfCards.at(i)->getId()){
                max = listOfCards.at(i)->getId();
                indexOfMax = i;
            }
        }
        return indexOfMax;
    }
}
int Tarot::getStrongestCardIndex(int indexCard1, int indexCard2) {

    Card *pCard1 = tapis.at(indexCard1);
    Card *pCard2 = tapis.at(indexCard2);

    // Pour savoir si la carte est un atout (type Card) ou non (type ColoredCard)
    auto *pColoredCard1 = dynamic_cast<ColoredCard *>(pCard1);
    auto *pColoredCard2 = dynamic_cast<ColoredCard *>(pCard2);

    // les 2 cartes ne sont pas des atouts (donc sont des cartes de couleurs (carreaux, coeurs, ...))
    if (pColoredCard1 != nullptr && pColoredCard2 != nullptr)
        return *pColoredCard1 > *pColoredCard2 ? indexCard1 : indexCard2;

    // les 2 cartes sont des atouts (donc ne sont pas des cartes de couleurs (carreaux, coeurs, ...))
    else if (pColoredCard1 == nullptr && pColoredCard2 == nullptr)
        return *pCard1 > *pCard2 ? indexCard1 : indexCard2;

    // 1 ere carte n'est pas un atout (la 2 ème si, et donc plus forte)
    else if (pColoredCard1 != nullptr)
        return indexCard2;
    else return indexCard1;
}

// gagnantDuPli est toujours le 1st player
// if gagnantDuPli = 0 then 2nd, 3rd, and 4th player are in indexes {1, 2, 3}
// if gagnantDuPli = 1 then 2nd, 3rd, and 4th player are in indexes {2, 3, 0}
// if gagnantDuPli = 2 then 2nd, 3rd, and 4th player are in indexes {3, 0, 1}
// if gagnantDuPli = 3 then 2nd, 3rd, and 4th player are in indexes {0, 1, 2}
Player *Tarot::get_ith_player(int _ith) {
    return joueurs.at((getIndexOfGagnantDuPli(gagnantDuPli)+(_ith-1))%4);
    }


float Tarot::getSumOfPointsInTapis() {
    float sum = 0;
    for(Card *pCard : tapis){
        sum+= pCard->getValue();
    }
    return sum;
}


//void Tarot::nextPlayer() {
//
//}




// Getters and Setters

const vector<Card *> &Tarot::getChien() const {
    return chien;
}

void Tarot::setChien(const vector<Card *> &_chien) {
    Tarot::chien = _chien;
}

int Tarot::getIdOfAttacker() const {
    return id_of_attacker;
}

Player *Tarot::getAttacker() {
    for (Player *player : joueurs) {
        if (player->getUniqueId() == id_of_attacker)
            return player;
    }
    return nullptr;
}

string Tarot::getName() const{
    return name;
}

Player *Tarot::getPlayerByID(int _id) {
    for(Player *player : joueurs){
        if(player->getUniqueId() == _id)
            return player;
    }
    return nullptr;
}

int Tarot::getIndexOfGagnantDuPli(const Player *_gagnantDuPli) {
    for (auto i = 0; i < joueurs.size(); i++){
        if(joueurs.at(i)->getUniqueId() == _gagnantDuPli->getUniqueId())
            return i;
    }
    return -1;
}

bool Tarot::cardPlayable(Card *toPlay) {
    auto * pColoredCard = dynamic_cast<ColoredCard*>(tapis.back());

    // Si la toute 1ere carte déjà posée sur le tapis est de type Atout, tout le monde doit jouer sa carte Atout
    // (et il faut que les cartes/chiffres des atous soient dans un ordre croissant)
    if(pColoredCard == nullptr){

        // dernière carte posée est à l'indice 0
        return (*toPlay > *tapis.at(0)) ? true : false;
    }

    // la toute 1ère carte déjà posée sur le tapis n'est pas un atout
    else if (tapis.at(0))
}
