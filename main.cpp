#include <algorithm>
#include "src/View.hpp"
#include "src/Controller.hpp"

int main() {
    Controller * controller;
    View* vue = new View();
    int jeu = View::printWelcomeInterface();
    do {
        controller = new Controller(vue, jeu);
        controller->startGame();

        int rejouer = View::rejouer();
        if(rejouer == 2) jeu = vue->printWelcomeInterface();
        if(rejouer == 3) break;
    }while (true);

    View::aurevoir();


    return 0;

}
