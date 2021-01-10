cmake_minimum_required(VERSION 3.17)
project(card-games-framework)

set(CMAKE_CXX_STANDARD 11)

add_executable(card-games-framework
	main.cpp
        src/Model/Game.hpp              src/Model/Game.cpp
        src/Model/Card.hpp              src/Model/Card.cpp
        src/Model/ColoredCard.hpp       src/Model/ColoredCard.cpp
        src/Model/Player.hpp            src/Model/Player.cpp
        src/Model/Deck.hpp              src/Model/Deck.cpp
        src/Model/Jeu/Bataille.hpp      src/Model/Jeu/Bataille.cpp
        src/Model/Jeu/UNO.hpp           src/Model/Jeu/UNO.cpp
        src/Model/Jeu/HuitAmericain.cpp src/Model/Jeu/HuitAmericain.hpp
		src/Model/Jeu/Belote.cpp        src/Model/Jeu/Belote.hpp
		src/Controller.cpp              src/Controller.hpp
		src/View.cpp                    src/View.hpp src/Model/Jeu/Tarot.cpp src/Model/Jeu/Tarot.hpp)