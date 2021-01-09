#include "src/View.hpp"
#include "src/Controller.hpp"


int main() {
    View* vue = new View();

    auto* controller = new Controller(vue, vue->printWelcomeInterface());
    controller->startGame();

}
