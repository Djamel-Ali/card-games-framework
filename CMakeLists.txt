cmake_minimum_required(VERSION 3.17)
project(card-games-framework)

set(CMAKE_CXX_STANDARD 11)

add_executable(card-games-framework
	main.cpp
        src/Model/Game.hpp src/Model/Game.cpp
        src/Model/Card.hpp src/Model/Card.cpp
        src/Model/ColoredCard.hpp src/Model/ColoredCard.cpp
        src/Model/Player.hpp src/Model/Player.cpp
        src/Model/Deck.hpp src/Model/Deck.cpp
        src/Model/Bataille.hpp src/Model/Bataille.cpp
        src/Model/UNO.hpp src/Model/UNO.cpp
        src/Model/HuitAmericain.cpp src/Model/HuitAmericain.hpp src/Model/Belote.cpp src/Model/Belote.hpp src/Controller.cpp src/Controller.hpp src/View.cpp src/View.hpp)