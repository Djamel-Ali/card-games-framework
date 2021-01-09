#include "View.hpp"
#include <limits>
View::View()
{
    controller = new Controller(this);
}

void View::start() {
    controller->setGame(printWelcomeInterface());
    controller->startGame();
}

int View::printWelcomeInterface() {
    cout << "---------------------------------------------------------" << endl;
    cout << "Bonjour, et bienvenu à notre platforme de jeux ! " << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Liste des jeux : " << endl;

    cout << "#1# LA BATAILLE" << endl;
    cout << "#2# LE HUIT AMERICAIN" << endl;
    cout << "#3# UNO" << endl;
    cout << "#4# LA BELOTE" << endl;
    cout << "#5# LE TAROT" << endl;


    int choix = 0;

    cout << "entrez un jeu entre 1 et 5" << endl;

    while (true)
    {
        cin >> choix;
        if (!cin || choix < 1 || choix > 5)
        {
            cout << "Erreur, merci d'entrer un jeu valide " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    }


    return choix;
}

void View::printPlayer(const Player &player) {
    cout << "tour de : " << endl;
    cout << player.getName() << endl;

}

void View::printHand(const Player &player) {
    int index = 0;
    for(Card* card: player.getHand()){
        cout << index << " : " << *card << endl;
        index ++;
    }
}

void View::update() {
    cout << *(controller ->game);

}

int View::play(int max, Player * player) {
    printPlayer(*player);

    int index = -1;

    cout << "entrez une carte entre 0 et "<< max << endl;

    while (true)
    {
        cin >> index;
        if (!cin || index < 0 || index > max)
        {
            cout << "Erreur, merci d'entrer une carte valide " << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else break;
    }

    return index;
}



