#ifndef CARD_GAMES_FRAMEWORK_TAROT_HPP
#define CARD_GAMES_FRAMEWORK_TAROT_HPP


#include "Card.hpp"
#include "Game.hpp"
#include "ColoredCard.hpp"

class Tarot : public Game {
private:
    static constexpr int PETITE = 1;
    static constexpr int GARDE = 2;
    static constexpr int GARDE_SANS_CHIEN = 3;
    static constexpr int GARDE_CONTRE_CHIEN = 4;

    vector<Card *> tapis;
    vector<Card *> chien;
    COLOR *colors;
    int id_of_attacker;

    //1 pour petite, 2 : garde, 3 : garde sans chien, 4 garde contre chien
    int strategy_of_attacker;

public:
    Tarot(const Deck &deck);

//    bool isWinner() override;
//
//    int getWinner() override;
//
//    int getIndexOfParseCard() override;
//
    void playRound(int indexCardToPlay) override;
//
//    void nextPlayer();

    void createCards() override;

    void startGame() override;




    // Getters and setters :

    const vector<Card *> &getChien() const;

    void setChien(const vector<Card *> &_chien);

    int getIdOfAttacker() const;

    Player *getAttacker();


    // Other methods

    // Phase dont laquelle un des joueur décide de jouer le role de l'attaquant
    void launchAnnouncementPhase();

    void displayChien();

    // fait appel à deux fonctions communes aux statégie PETITE et GARDE
    void integrateThenDiscard();

    // Ajouter les cartes du chien à la main de l'attaquant
    void integrateChien();

    // L'attaquant choisit les 6 cartes à écarter de sa main (pour les remettre au chien)
    void discardAdditionalCards();

    static bool moveCardFromTo(vector<Card *> &srcVectOfCards, vector<Card *> &targetVectOfCards, int idOfCard);

};


#endif //CARD_GAMES_FRAMEWORK_TAROT_HPP
