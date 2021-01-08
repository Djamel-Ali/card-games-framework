#include <iostream>
#include "Game.hpp"
#include "Tarot.hpp"

Game::Game(const Deck &_deck) : deck(_deck) {
    std::cout << "Construction of Game" << std::endl;
}

void Game::initGame() {
    createCards();
    deck.shuffleCards();
}

Card *Game::getCardById(const vector<Card *> &vect_of_cards, int card_id) {
    for(Card *pCard : vect_of_cards){
        if(pCard->getId() == card_id)
            return pCard;
    }
    return nullptr;
}

void Game::moveFromTo(vector<Card *> src, vector<Card *> dest) {

}

std::ostream &operator<<(std::ostream &out, const Game &a_game) {
    out << "\n\n\t" << a_game.getName() << a_game.printGameBoard() << a_game.printPlayers();
    return out;
}
