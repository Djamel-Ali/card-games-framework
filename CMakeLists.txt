cmake_minimum_required(VERSION 3.17)
project(card_games_framework)

set(CMAKE_CXX_STANDARD 11)

add_executable(card_games_framework main.cpp
        src/Card.cpp src/Card.hpp
        src/ColoredCard.cpp src/ColoredCard.hpp
        src/Game.cpp src/Game.hpp
        src/Bataille.cpp src/Bataille.hpp
        src/Player.cpp src/Player.hpp src/Deck.cpp src/Deck.hpp)