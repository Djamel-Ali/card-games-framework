#include "src/View.hpp"
#include "src/Controller.hpp"

int main() {
    Controller * controller;
    View* vue = new View();

    do {
        controller = new Controller(vue, vue->printWelcomeInterface());
        controller->startGame();
        if(vue->rejouer()) break;
    }while (true);

    vue->aurevoir();
    return 0;
}
