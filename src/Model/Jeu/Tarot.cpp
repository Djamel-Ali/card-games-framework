#include <iostream>
#include "Tarot.hpp"
#include <algorithm>

Tarot::Tarot(Deck *pDeck) : Game(pDeck), index_of_attacker{-1}, goal_of_the_attacker{56}, strategy_of_attacker{-1},
                                         coefficient_contrat{1}, gagnantDuPli{getAttacker()}{
    joueurs.push_back(new Player("Djamel", vector<Card *> {}, 0));
    joueurs.push_back(new Player("Mandela", vector<Card *> {}, 0));
    joueurs.push_back(new Player("Yacine", vector<Card *> {}, 0));
    joueurs.push_back(new Player("Ghandi", vector<Card *> {}, 0));

}

void Tarot::createCards() {
    COLOR symbols[] = {TREFLE, COEUR, CARREAU, PIQUE, NONE};


    /// N.B: LES NON-ATOUTS SONT DE TYPE ColoredCard
    // [1..10] * 4 = 40 cartes basses (ou blanches) valent chacune 0,5 point (soit un total de 20 points) ;
    for (int numero = 1; numero <= 10; numero++) {
        for (int symbol = 0; symbol < 4; symbol++) {
            deck->addCard(new ColoredCard(to_string(numero), numero, 0.5, symbols[symbol]));
        }
    }

    /// N.B: LES ATOUTS SONT DE TYPE Card
    // [2..20] = 19 atouts du n°2 au n°20 valent chacun 0,5 point (soit un total de 9,5 points) ;
    for (int numero = 2; numero <= 20; numero++) {
        deck->addCard(new Card(to_string(numero), numero, 0.5));
    }

    // les 4 Valets valent chacun 1,5 point (soit un total de 6 points) ;
    // les 4 Cavaliers valent chacun 2,5 points (soit un total de 10 points) ;
    // les 4 Dames valent chacune 3,5 points (soit un total de 14 points) ;
    // les 4 Rois valent chacun 4,5 points (soit un total de 18 points) ;
    for (int symbol = 0; symbol < 4; symbol++) {
        deck->addCard(new ColoredCard("VALET", 11, float(1.5), symbols[symbol]));
        deck->addCard(new ColoredCard("CAVALIER", 12, 2.5, symbols[symbol]));
        deck->addCard(new ColoredCard("DAME", 13, 3.5, symbols[symbol]));
        deck->addCard(new ColoredCard("ROI", 14, 4.5, symbols[symbol]));
    }

    // les 3 Bouts valent chacun 4,5 points (soit un total de 13,5 points) ;
    // (les cartes 1 et 21 d'atout + l'EXCUSE)
    for (int numero = 1; numero <= 21; numero += 20) {
        deck->addCard(new Card(to_string(numero), numero, 4.5));
    }
    // la carte 22 d'atout (l'EXCUSE)
    deck->addCard(new Card("EXCUSE", 22, 4.5));

}


void Tarot::distribution() {

    // Au total 18 cartes par joueur (distribue à chaque joueur les cartes 3 par 3)
    for(auto i = 0; i < 6; i++)
        deck->distributeCards(3, joueurs);
    cout << "\nCartes distribuées aux players" << endl;

    // 6 cartes restantes dans le deck seront mises dans le talon (ou le chien)
    setChien(deck->getDeckOfCards());


    // Launch the announcement phase
    launchAnnouncementPhase();
    // À la sortie de cette methode (phase des annonces) on saurait qui est le meneur et qui sont les défenseurs


    // L'attaquant (le preneur) jouera la toute 1ère carte
    actualPlaying = getIndexOfPlayer(getAttacker());
}

// Other methods :

// Phase dont laquelle un des joueurs décide de jouer le role de l'attaquant
void Tarot::launchAnnouncementPhase() {
    int choice = -1;
    while (index_of_attacker == -1) {
        for (auto i = 0; i < (int)(int)joueurs.size(); i++) {
            joueurs.at(i)->displayHand();

            cout << "\n\t1 : Passe \n\t2 : PETITE \n\t3 : GARDE \n\t4 : GARDE SANS CHIEN \n\t5 : GARDE CONTRE CHIEN"
                 << endl;
            cout << "\n\tVeuillez saisir le numéro correspondant à votre choix : " << endl;
            cin >> choice;
            switch (choice) {
                case 1 : // passe
                    continue;
                case 2 : // PETITE
                    index_of_attacker = i;

                    // L'attaquant (ou le preneur) de la donne courante,
                    // joue la toute première carte de la cette donne,
                    // (aussi il faut initialiser le gagnant du pli par l'attaquant courant car
                    // c'est le gagant du pli courant qui débutera le pli suivant)
                    setGagnantDuPli(joueurs.at(index_of_attacker));

                    strategy_of_attacker = PETITE;
                    cout << "\n\n\tType de contrat : PETITE --> l'attaquant montre les cartes du chien à ses partenaires :\n\n";
                    displayChien();

                    // Sur ce contrat (PETITE) les cartes du chien seront intégrées dans la main du preneur, ensuite
                    // le preneur doit écarter 6 cartes de son choix de sa main (qui contient actuellement 24 cartes)
                    integrateThenDiscard();
                    // Les 6 cartes récemment écartées (mises dans Chien) vont rester secrètes tout au long de la partie
                    break;
                case 3 : // GARDE
                    index_of_attacker = i;
                    setGagnantDuPli(joueurs.at(index_of_attacker));
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
                    index_of_attacker = i;
                    setGagnantDuPli(joueurs.at(index_of_attacker));
                    strategy_of_attacker = GARDE_SANS_CHIEN;

                    //Coefficients des différents contrats :
                    //PETITE = 1, GARDE = 2, GARDE SANS CHIEN = 4, GARDE CONTRE CHIEN = 6
                    coefficient_contrat = 4;
                    break;
                case 5 : // GARDE CONTRE CHIEN
                    index_of_attacker = i;
                    setGagnantDuPli(joueurs.at(index_of_attacker));
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
            if(index_of_attacker> -1)
                break;
        }
        // Si personne ne s'est présenté comme preneur (attaquant) tout le monde remet ses cartes au Deck,
        // on mélange, on redistribue, puis on recommence et ainsi de suite jusqu'à ce ce qu'on trouve un attaquant
        if (index_of_attacker == -1) {
            collectAllTheCards();
            deck->shuffleCards();
            distribution();
        }
    }
}

void Tarot::displayChien() {
    cout << "Chien : ";
    for (Card *pCard : chien) {
        cout << *pCard << " ; ";
    }
    cout << "\n";
}

// Ajouter les cartes du chien à la main de l'attaquant
void Tarot::integrateChien() {
    while (!chien.empty()){
        joueurs.at(index_of_attacker)->addCard(chien.back());
        chien.pop_back();
    }
}

// L'attaquant choisit les 6 cartes à écarter de sa main qui en contient actuellement 24
// (pour les remettre au Chien)
void Tarot::discardAdditionalCards() {
    int indexOfCardToBeDiscarded = -1;
    for (auto i = 6; i > 0; i--) {
        while (true)
        {
            getAttacker()->displayHand();
            cout << "\n\t" << i << " carte(s) à écarter : " << endl;
            cout << "\tSaisissez l'indice de la carte à écarter svp : ";
            cin >> indexOfCardToBeDiscarded;
            if (!cin || indexOfCardToBeDiscarded < 0 || indexOfCardToBeDiscarded > (int)joueurs.at(index_of_attacker)->getHand().size()-1)
            {
                cout << "Erreur, merci d'entrer une carte valide " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else break;
        }
        chien.push_back(joueurs.at(index_of_attacker)->playCard(indexOfCardToBeDiscarded));
    }
}


// ajoute les carte du chien à la main du preneur, puis laisse ce dernier choisir les 6 cartes à écarter
void Tarot::integrateThenDiscard() {
    integrateChien();
    discardAdditionalCards();
}

bool Tarot::isWinner() {
    for (Player *player : joueurs) {
        if (player->getCurrentScore() >= GAMEPLAY_OBJECTIVE)
            return true;
    }
    return false;
}

// Returns the winner's ID
int Tarot::getWinner() {
    for (auto i =0; i < (int)joueurs.size(); i++) {
        if (joueurs.at(i)->getCurrentScore() >= GAMEPLAY_OBJECTIVE)
            return i;
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

/*
//L'attaquant (de la donne courante) joue toujours en premier pour débuter la partie,
//Le gagant du pli courant débutera le pli suivant (et puis dans le sens aiguilles d'une montre)
void Tarot::playRound(int indexCardToPlay) {

    if (endOfDonne()) {
        updatesScores();
        collectAllTheCards();
        deck->shuffleCards();
        distribution();

        // Launch the announcement phase
        launchAnnouncementPhase();
        actualPlaying = index_of_attacker;
        // À la sortie de cette methode (phase des annonces) on saurait qui est le meneur et qui sont
        // les défenseurs pour la donne qui suit
    }
    else{

        //L'attaquant joue toujours en premier à la première donne,
        // sinon par le gagnant du pli à chaque à chaque fois pour toutes les autres donnes
        // (pour ça le gagnant du pli est initialisé au départ par le preneur)
        if(tapis.empty())
        {
            tapis.insert(tapis.begin(), joueurs.at(actualPlaying)->playCard(indexCardToPlay));
            nextPlayer();
        }
        else{
            if(cardPlayable
                    (joueurs.at(actualPlaying)->getHand().at(indexCardToPlay), *joueurs.at(actualPlaying)))
            {
                tapis.insert(tapis.begin(), joueurs.at(actualPlaying)->playCard(indexCardToPlay));
                nextPlayer();
            }
            else cout << "\n\n\tLa carte ne peut pas etre jouée, veuillez en choisir une autre svp\n";
        }
    }

    if (tapis.size() == 4){

        // Les (3) autres joueurs joueront après lui (le gagnant du pli précédent), un par un.
        makeTheOthersPlay();

        // À la sortie de cette méthode, on aurait mis à jour le gagnantDuPli
        // (donc on calcule la somme des points qu'il vient de gagner sur ce pli)
        gagnantDuPli->setCurrentScore(gagnantDuPli->getCurrentScore()+getSumOfPointsInTapis());

        actualPlaying = getIndexOfGagantDuPli();

        // Récupération des carte du tapis et on les remet directement dans le deck
        // (car le score est mis à jour au fur et à mesure)
        deck->getDeckOfCards().insert(deck->getDeckOfCards().end(), tapis.begin(), tapis.end());
        tapis.clear();
    }
}
*/
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
        getAttacker()->setCurrentScore(getAttacker()->getCurrentScore() + 3 * newGain);
        updateDefendersScores((-1) * newGain);
    } else {
        cout << "L'attaquant n'a pas réussi à réaliser son contrat !" << endl;
        cout << "\n\tL'attaquant :  " << newGain * (-3) << " pts." << endl;
        cout << "\tLes défenseurs : + " << newGain << " pts chacun.";

        getAttacker()->setCurrentScore(getAttacker()->getCurrentScore() - 3 * newGain);
        updateDefendersScores(newGain);
    }
    displayCalculationSummary();
    getAttacker()->setCurrentScore(0);
}

// mise à jour des scores (finaux et intermediaires) des défenseurs de la donne courante
void Tarot::updateDefendersScores(float newGain) {
    for (auto i =0; i < (int)joueurs.size(); i++) {
        if (i != index_of_attacker) {
            joueurs.at(i)->setCurrentScore(joueurs.at(i)->getCurrentScore() + newGain);
        }
    }
}

// Display the final scores of the other players (other than the attacker of the deal that just finished).
void Tarot::displayDefendersFinalScores() {
    for (auto i =0; i < (int)(int)joueurs.size(); i++) {
        if (i != index_of_attacker) {
            cout << *joueurs.at(i) << endl;
        }
    }
}

void Tarot::displayFinalResults() {
    for (Player *player : joueurs) {
        cout << *player;
    }
    cout << "\n----------------------------------------------------------------------" << endl;
    cout << "Tapis : " << endl;

    for(Card *card : tapis){
        auto temp = dynamic_cast<ColoredCard*>(card);
        if(temp)
            cout << *temp;
        else
            cout << *card;
        cout << " - " ;
    }
    cout << "\n----------------------------------------------------------------------" << endl;

    joueurs.at(actualPlaying)->displayHand();
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

    cout << "score final de l'attaquant: " << getAttacker()->getCurrentScore()
         << " ( id de l'attaquant : " << index_of_attacker << " )" << endl;
    cout << "scores finaux des défenseurs: " << endl;
    displayDefendersFinalScores();
}


// Faire jouer les 3 autres joueurs après le que le gagnant du pli précédent ait joué
void Tarot::makeTheOthersPlay() {
    // Les 3 autres joueurs viennent de jouer chacun sa carte

    // Mettre à jour le joueur qui va gagner le pli courant
    // D'abord trouver le joueur qui a posé la carte la plus forte
    // (c'est lui le gagnant du pli, donc on doit mettre à jour cette variable)
    int strongestCardIndex = getIndexOfParseCard();
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
        for(auto i = 1; i < (int)listOfCards.size(); i++){
            if(max < listOfCards.at(i)->getId()){
                max = listOfCards.at(i)->getId();
                indexOfMax = i;
            }
        }
        return indexOfMax;
    }
}

// gagnantDuPli est toujours le 1st player
// if gagnantDuPli = 0 then 2nd, 3rd, and 4th player are in indexes {1, 2, 3}
// if gagnantDuPli = 1 then 2nd, 3rd, and 4th player are in indexes {2, 3, 0}
// if gagnantDuPli = 2 then 2nd, 3rd, and 4th player are in indexes {3, 0, 1}
// if gagnantDuPli = 3 then 2nd, 3rd, and 4th player are in indexes {0, 1, 2}
Player *Tarot::get_ith_player(int _ith) {
    return joueurs.at((getIndexOfPlayer(gagnantDuPli) + (_ith - 1)) % 4);
}


float Tarot::getSumOfPointsInTapis() {
    float sum = 0;
    for(Card *pCard : tapis){
        sum+= pCard->getValue();
    }
    return sum;
}


void Tarot::nextPlayer() {
    if (endOfDonne()) {
        updatesScores();
        collectAllTheCards();
        deck->shuffleCards();
        distribution();

        // Launch the announcement phase
        launchAnnouncementPhase();
        actualPlaying = index_of_attacker;
        // À la sortie de cette methode (phase des annonces) on saurait qui est le meneur et qui sont
        // les défenseurs pour la donne qui suit
    }


    actualPlaying++;
    actualPlaying = actualPlaying % (int)(int)joueurs.size();
    5
    if (tapis.size() == 4){

        // Les (3) autres joueurs joueront après lui (le gagnant du pli précédent), un par un.
        makeTheOthersPlay();

        // À la sortie de cette méthode, on aurait mis à jour le gagnantDuPli
        // (donc on calcule la somme des points qu'il vient de gagner sur ce pli)
        gagnantDuPli->setCurrentScore(gagnantDuPli->getCurrentScore()+getSumOfPointsInTapis());

        actualPlaying = getIndexOfGagantDuPli();

        // Récupération des carte du tapis et on les remet directement dans le deck
        // (car le score est mis à jour au fur et à mesure)
        deck->getDeckOfCards().insert(deck->getDeckOfCards().end(), tapis.begin(), tapis.end());
        tapis.clear();
    }


}

void Tarot::setChien(vector<Card *> &_chien) {
    while (!_chien.empty()){
        chien.push_back(_chien.back());
        _chien.pop_back();
    }
}

Player *Tarot::getAttacker() {
    for (auto i = 0; i< (int)joueurs.size(); i++) {
        if (i == index_of_attacker)
            return joueurs.at(i);
    }
    return nullptr;
}

string Tarot::getName() const{
    return name;
}

int Tarot::getIndexOfPlayer(const Player *_pPlayer) {
    for (auto i = 0; i < (int)joueurs.size(); i++){
        if(joueurs.at(i) == _pPlayer)
            return i;
    }
    return -1;
}



bool Tarot::cardPlayable(Card *toPlay, const Player &concernedPlayer) {
    if(!tapis.empty()) {
        cout << "test playable Card de Tarto" << endl;
        bool response = false;
        auto pPlayedColoredCard =  dynamic_cast<ColoredCard*>(tapis.back());


        auto pToPlayColoredCard = dynamic_cast<ColoredCard*>(toPlay);

        // Si la toute 1ere carte déjà posée sur le tapis est de type Atout, tout le monde doit jouer sa carte Atout
        // (et il faut que les cartes/chiffres des atous soient dans un ordre croissant)
        if(pPlayedColoredCard == nullptr){

            // la carte à jouer est aussi de type atout, (donc il faut juste qu'elle soit plus grande que celles déjà posées)
            if(pToPlayColoredCard == nullptr){
                auto i = 0;
                while (i < (int)tapis.size()){
                    // dernière carte posée est à l'indice 0 (elle devait être atout, mais elle peut ne pas l'être)
                    auto pColoredCard = dynamic_cast<ColoredCard*>(tapis.at(i));

                    // si la carte déjà posée est de type atout, et celle qu'on veut poser est plus grande qu'elle,
                    // alors on peut retourner True
                    if (pColoredCard == nullptr && *toPlay > *tapis.at(i))
                        response = true;
                    else
                        i++;
                }
            }
                // il faut jouer un atout, mais la carte à jouer n'est pas un atout,
                // donc il faut vérifier qu'il n'existe vraiment pas d'atout dans la main du joueur pour dire oui
            else{
                if(noAtoutInHand(concernedPlayer))
                    response = true;

                //sinon, s'il existe au moins un atout dans la main du player et donc il doit jouer un atout
                // cette fois-ci (pas la peine d'ecrire un else puis response = false car reste elle est déjà à false).
            }
        }

            // Si la toute 1ere carte déjà posée sur le tapis est de type couleur (non-atout), tout le monde doit jouer
            // la meme couleur, s'il y'en a pas il faut jouer un atout, si pas d'atout, jouer n'importe quelle autre carte.
        else{

            // si le joueur veut couper la couleur par un atout, il faut vérifier qu'il n'a vraiment pas cette
            // couleur dans sa main pour dire ok, sinon on l'olblige à jouer une des carte de cette couleur qu'il a en main.
            if(pToPlayColoredCard == nullptr){
                // il n'a vraiment pas cette couleur --> ok
                if(noColorInHand(pPlayedColoredCard->getColor(), concernedPlayer )){
                    response = true;
                }
                // le else reste a false.
            }

                // la carte attendu est de type couleur, le joueur veut aussi poser une carte de couleur,
                // --> il faut vérifier que les deux cartes sont de meme couleur;
            else{
                if(pToPlayColoredCard->getColor() == pPlayedColoredCard->getColor())
                    response = true;
            }
            // dans le else; la var response est déjà initialisée à false;
        }
        return response;
    }

    return true;
}

bool Tarot::noAtoutInHand(const Player &player) {
    for(Card * pCard : player.getHand()){
        auto pColoredCard = dynamic_cast<ColoredCard*>(pCard);

        // Atout est de type Card et non pas de type ColoredCard
        if (pColoredCard == nullptr)
            return false;
    }
    return true;
}

bool Tarot::noColorInHand(COLOR expectedColor, const Player &_player) {
    for(Card * card : _player.getHand()){
        auto pColored = dynamic_cast<ColoredCard*>(card);

        // si c'est une carte de couleur, on vérifie si c'est la couleur attendue
        if(pColored != nullptr){
            if(pColored->getColor() == expectedColor)
                return false;
        }
    }
    return true;
}

int Tarot::getIndexOfParseCard() {
    return getStrongestCardIndex(tapis);
}

void Tarot::print(ostream &out) {
    displayFinalResults();
}

int Tarot::getIndexOfGagantDuPli() {
    for(auto i = 0; i < (int)joueurs.size(); i++){
        if(joueurs.at(i) == gagnantDuPli)
            return i;
    }
    return -1;
}

// récupération de toutes les cartes (mains des joueurs et leurs réserves (cartes gagnées) + Le Chien)
// pour les mettre dans Deck
void Tarot::collectAllTheCards() {
    // Récupération des cartes des joueurs
    for (Player *player : joueurs)
    {
        while (!player->getHand().empty()){
            deck->addCard(player->playCard(0));
        }
    }
    while (!chien.empty()) {
        // Récupération des carte du chien et on met tout dans deck
        deck->addCard(chien.back());
        chien.pop_back();
    }
}

bool Tarot::cardPlayable(Card *toPlay) {
    cout << "actual ===" << actualPlaying << endl;
    const Player &temp = *joueurs[actualPlaying];
    return cardPlayable(toPlay, temp);
}
