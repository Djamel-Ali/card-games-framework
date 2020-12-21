cmake_minimum_required(VERSION 3.17)
project(card-games-framework)

set(CMAKE_CXX_STANDARD 11)

add_executable(main.cpp
        src/Game.hpp src/Game.cpp
        src/Card.hpp src/Card.cpp
        src/ColoredCard.hpp src/ColoredCard.cpp
        src/Player.hpp src/Player.cpp
        src/Deck.hpp src/Deck.cpp
        src/Bataille.hpp src/Bataille.cpp
        src/UNO.hpp src/UNO.cpp
        src/HuitAmericain.cpp src/HuitAmericain.hpp)