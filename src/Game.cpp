#include <iostream>
#include "Game.hpp"

Game::Game(const Deck &_deck) : deck(_deck) {
    std::cout << "Construction of Game" << std::endl;
}

void Game::initGame() {
    createCards();
    deck.shuffleCards();
}

