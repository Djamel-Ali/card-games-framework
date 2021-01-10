CPP=g++ --std=c++11 -Wall

all : main

main : main.o View.o Controller.o Game.o Deck.o Player.o Card.o ColoredCard.o Bataille.o HuitAmericain.o UNO.o Belote.o
	$(CPP) -o main main.o View.o Controller.o Game.o Deck.o Player.o Card.o ColoredCard.o Bataille.o HuitAmericain.o UNO.o Belote.o

main.o : main.cpp
	$(CPP) -c main.cpp

View.o : src/View.cpp
	$(CPP) -c src/View.cpp

Controller.o : src/Controller.cpp
	$(CPP) -c src/Controller.cpp

Game.o: src/Model/Game.cpp
	$(CPP) -c src/Model/Game.cpp

Deck.o : src/Model/Deck.cpp
	$(CPP) -c src/Model/Deck.cpp

Player.o : src/Model/Player.cpp
	$(CPP) -c src/Model/Player.cpp

Card.o : src/Model/Card.cpp
	$(CPP) -c src/Model/Card.cpp

ColoredCard.o : src/Model/ColoredCard.cpp
	$(CPP) -c src/Model/ColoredCard.cpp

Bataille.o : src/Model/Jeu/Bataille.cpp
	$(CPP) -c src/Model/Jeu/Bataille.cpp

HuitAmericain.o : src/Model/Jeu/HuitAmericain.cpp
	$(CPP) -c src/Model/Jeu/HuitAmericain.cpp

UNO.o : src/Model/Jeu/UNO.cpp
	$(CPP) -c src/Model/Jeu/UNO.cpp

Belote.o : src/Model/Jeu/Belote.cpp
	$(CPP) -c src/Model/Jeu/Belote.cpp

clean :
	rm *.o