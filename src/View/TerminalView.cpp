#include <iostream>
#include "TerminalView.hpp"

using namespace std;

void TerminalView::printWelcomeInterface() {
    cout << "\n---------------------------------------------------------\n\n"
            "Bonjour, et bienvenu à notre platforme de jeux !\n"
            "\n---------------------------------------------------------\n\n"
            "Liste des jeux : \n"

            "#1# LA BATAILLE\n"
            "#2# 8 AMERICAIN\n"
            "#3# UNO\n"
            "#4# LA BELOTE\n"
            "#5# LE TAROT\n"

            "Saisissez le numéro correspondant à votre choix svp : " ;
}

void TerminalView::printPlayer(const Player &player) {
    cout << player;
}

void TerminalView::printHand(const Player &player) {
    player.displayHand();
}