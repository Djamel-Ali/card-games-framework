#ifndef CARD_GAMES_FRAMEWORK_TERMINALVIEW_HPP
#define CARD_GAMES_FRAMEWORK_TERMINALVIEW_HPP


#include "../Player.hpp"
#include "../Game.hpp"

class TerminalView {
private:
public:
    static void printWelcomeInterface();
    static void printPlayer(const Player &player);
    static void printHand(const Player &player);

};

/// Surcharge de l’opérateur <<
std::ostream &operator<<(std::ostream &out, const Game &a_game);

#endif //CARD_GAMES_FRAMEWORK_TERMINALVIEW_HPP
