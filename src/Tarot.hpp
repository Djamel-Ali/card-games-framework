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
    static constexpr int GAMEPLAY_OBJECTIVE = 100;

    static vector<Card *> tapis;
    vector<Card *> chien;
    COLOR *colors;
    int id_of_attacker;
    Player *gagnantDuPli;

    // Le nombre de point que l'attaquant doit atteindre à la fin de la partie (initialement 56 pts, mais peut diminuer
    // à 51, 41 ou 36 s'il a 1 bout, 2 bouts ou 3 bouts respectivement dans les cartes gagnées à la fin de la partie)
    int goal_of_the_attacker;

    //1 pour petite, 2 : garde, 3 : garde sans chien, 4 garde contre chien
    int strategy_of_attacker;

    // PETITE = 1, GARDE = 2, GARDE SANS CHIEN = 4, GARDE CONTRE CHIEN = 6
    int coefficient_contrat;

public:
    explicit Tarot(const Deck &deck);

    // Returns 'true' when you reach the end of the gameplay.
    bool isWinner() override;

    // Returns 'true' when you reach the end of the donne (une partie de jeu se compose de plusieurs de donnes) .
    //checks that all Hands Are Empty
    bool endOfDonne();

    // Returns the winner's ID
    int getWinner() override;

//    int getIndexOfParseCard() override;

    //L'attaquant joue toujours en premier
    void playRound(int indexCardToPlay) override;

//    void nextPlayer();

    void createCards() override;

    void startGame() override;




    // Getters and setters :

    const vector<Card *> &getChien() const;

    void setChien(const vector<Card *> &_chien);

    int getIdOfAttacker() const;

    Player *getAttacker();

    // indexes [0..3]
    Player *getDefenderOfIndex(int index);

    Player *getGagnantDuPli() const;

    void setGagnantDuPli(Player *_gagnantDuPli);


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

    // update current and final scores of players
    void updatesScores();

    // mis à jour les scores finaux des défenseurs de la donne courante
    void updateDefenderScores(int newGain);

    //todo: il faut changer : attaquant n'est pas fix pour toute la partie (donc pour modifier toutes les méthodes
    // concernées en passant à chaque fois l'ID de l'attaquant courant par e.g.)

    // Afficher les scores des autres joueurs (autre que l'attaquant de la donne qui vient de finir).
    void displayDefendersScores();

    // Affiche les résultats finaux
    void displayFinalResults();

    // Affiche les résultats intermediaires
    void displayIntermediateResults();

    // Affiche les résultats intermediaires avec des explications détatillées du comptage de points
    void displayPointCountingExplanations();

    // récupération de toutes les cartes (mains des joueurs + Le Chien) pour les mettre dans Deck
    void collectHandsAndChien();

    // récupération de toutes les cartes (qui sont dans les réserves de chaque joueur qui comprennent le Chien)
    // pour les mettre dans Deck
    void collectReservesOfPlayers();

    // Returns 'true' when One of the players won (i.e. it reaches or exceeds the target number of points).
    bool oneOfThePlayersWon();

    void makeTheDefendersPlay();

    static int getStrongestCardId(int idCard1, int idCard2);

    static float getSumOfPointsInTapis();




};


#endif //CARD_GAMES_FRAMEWORK_TAROT_HPP
