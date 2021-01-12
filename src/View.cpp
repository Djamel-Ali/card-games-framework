#include "View.hpp"

#include <limits>

View::View()
{
}

View::~View() {
    delete game;
}

int View::rejouer() {
    int choice;
    cout << "\n----------------------------------" << endl;
    cout << "LA PARTIE EST TERMINÉE" << endl;
    cout << "\n----------------------------------\n" << endl;

    cout << "1 : REJOUER;  2 : QUITTER" << endl;
    cin >> choice;

    if (!cin || choice < 1 || choice > 2)
    {
        cout << "Erreur, merci d'entrer un choix valide " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice == 2 ? 1 : 0;
}

void View::aurevoir() {
    cout << "\n\n AU REVOIR :) \n\n" << endl;
}

int View::printWelcomeInterface() {
    cout << "---------------------------------------------------------" << endl;
    cout << "Bonjour et bienvenue à notre platforme de jeux ! " << endl;
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

void View::printWinner(const Player &player) {
    cout << "Bravo, ";
    cout << player.getName() << " ";
    cout << "a gagné !" << endl;

}


void View::update() {
    cout << *(game);

}

int View::play(int max, Player * player) {
    if(player->isBot()){
        return game->playAuto();
    }
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

void View::setGame(Game *_game) {
    game = _game;
}

void View::cantPlay() {
    cout << "aucune de tes cartes n'est jouable" << endl;
    cout << "tu passes ton tour" << endl;
    system("pause");
}




