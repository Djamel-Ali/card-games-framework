#include <iostream>
#include "Tarot.hpp"
#include <algorithm>

Tarot::Tarot(const Deck &deck) : Game(deck), id_of_attacker{-1}, strategy_of_attacker{-1} {
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

    // Launch the announcement phase
    launchAnnouncementPhase();
    // À la sortie de cette methode (phase des annonces) on saurait qui est le meneur et qui sont les défenseurs
}

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
    for(Player *player : joueurs){
        if(player->getUniqueId() == id_of_attacker)
            return player;
    }
    return nullptr;
}

// Other methods :

// Phase dont laquelle un des joueur décide de jouer le role de l'attaquant
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
                case 2 :
                    id_of_attacker = pPlayer->getUniqueId();
                    strategy_of_attacker = PETITE;
                    cout << "Type de contrat : PETITE --> l'attaquant montre les cartes du chien à ses partenaires :\n";
                    displayChien();
                    // Sur ce contrat (PETITE) les cartes du chien seront intégrées dans la main du preneur, ensuite
                    // le preneur doit écarter 6 cartes de son choix de sa main (qui contient actuellement 24 cartes)
                    integrateThenDiscard();
                    // Les 6 cartes récemment écartées (mises dans Chien) vont rester secrètes tout au long de la partie
                    break;
                case 3 :
                    id_of_attacker = pPlayer->getUniqueId();
                    strategy_of_attacker = GARDE;
                    cout << "Type de contrat : GARDE --> l'attaquant montre les cartes du chien à ses partenaires :\n";
                    displayChien();
                    // Sur ce contrat (GARDE) les cartes du chien seront intégrées dans la main du preneur, ensuite
                    // le preneur doit écarter 6 cartes de son choix de sa main (qui contient actuellement 24 cartes)
                    integrateThenDiscard();
                    // Les 6 cartes récemment écartées (mises dans Chien) vont rester secrètes tout au long de la partie
                    break;
                case 4 :
                    id_of_attacker = pPlayer->getUniqueId();
                    strategy_of_attacker = GARDE_SANS_CHIEN;
                    break;
                case 5 :
                    id_of_attacker = pPlayer->getUniqueId();
                    strategy_of_attacker = GARDE_CONTRE_CHIEN;
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
            for (Player *player : joueurs)
                player->putBackHand(deck);
            deck.shuffleCards();
            deck.distributeCards(18, joueurs);
        }
    }
}

void Tarot::displayChien() {
    cout << "Chien : ";
    for(Card *pCard : chien){
        cout << *pCard << " ; ";
    }
}

// Ajouter les cartes du chien à la main de l'attaquant
void Tarot::integrateChien() {
    for (Player *pJoueur : joueurs){
        if(pJoueur->getUniqueId() == id_of_attacker){
            pJoueur->getHand().insert(pJoueur->getHand().end(), chien.begin(), chien.end());
            chien.clear();
        }
    }
}

// L'attaquant choisit les 6 cartes à écarter de sa main (pour les remettre au chien)
void Tarot::discardAdditionalCards() {
    int idOfCardToBeDiscared = -1;
    for (auto i = 6 ; i > 0 ; i--){
        bool done = false;
        do{
            getAttacker()->displayHand();
            cout << "\n\t" << i << " carte(s) à écarter : " << endl;
            cout << "\tSaisissez l'identifiant de la carte à écarter : ";
            cin >> idOfCardToBeDiscared;
            done = moveCardFromTo(getAttacker()->getHand(), chien, idOfCardToBeDiscared);
        } while (!done);
    }
}

bool Tarot::moveCardFromTo(vector<Card *> &srcVectOfCards, vector<Card *> &targetVectOfCards, int idOfCard) {
    for(Card* pCard : srcVectOfCards){
        if(pCard->getId() == idOfCard)
        {
            targetVectOfCards.push_back(pCard);
            //explanation found on stackoverflow (regarding How do to remove an item from
            // a stl vector with a certain value) link : https://stackoverflow.com/a/39944
            srcVectOfCards.erase(remove(srcVectOfCards.begin(), srcVectOfCards.end(), pCard), srcVectOfCards.end());
            return true;
        }
    }
    return false;
}

void Tarot::integrateThenDiscard() {
    integrateChien();
    discardAdditionalCards();
}





//bool Tarot::isWinner() {
//    return false;
//}
//
//int Tarot::getWinner() {
//    return 0;
//}
//
//int Tarot::getIndexOfParseCard() {
//    return 0;
//}

void Tarot::playRound(int indexCardToPlay) {

}

//void Tarot::nextPlayer() {
//
//}
