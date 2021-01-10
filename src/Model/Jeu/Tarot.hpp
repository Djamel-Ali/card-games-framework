#ifndef CARD_GAMES_FRAMEWORK_TAROT_HPP
#define CARD_GAMES_FRAMEWORK_TAROT_HPP


#include "../Game.hpp"
#include "../ColoredCard.hpp"

class Tarot : public Game {
private:
    const string name;

    // constantes qui représentent les différents types de contrats (ou de stratégies)
    static constexpr int PETITE = 1;
    static constexpr int GARDE = 2;
    static constexpr int GARDE_SANS_CHIEN = 3;
    static constexpr int GARDE_CONTRE_CHIEN = 4;

    // constante qui représente le score que doit atteindre le gagnant de la partie de Tarot.
    static constexpr int GAMEPLAY_OBJECTIVE = 150;

    vector<Card *> tapis;
    vector<Card *> chien;
    int index_of_attacker;

    // Le nombre de point que l'attaquant doit atteindre à la fin de la donne (initialement 56 pts, mais peut diminuer
    // à 51, 41 ou 36 s'il a 1 bout, 2 bouts ou 3 bouts respectivement dans les cartes gagnées à la fin de la partie)
    int goal_of_the_attacker;

    //1 pour petite, 2 : garde, 3 : garde sans chien, 4 garde contre chien
    int strategy_of_attacker;

    // PETITE = 1, GARDE = 2, GARDE SANS CHIEN = 4, GARDE CONTRE CHIEN = 6
    int coefficient_contrat;

    Player *gagnantDuPli;


public:
    explicit Tarot(Deck *pDeck);

    // Returns 'true' when you reach the end of the gameplay.
    bool isWinner() override;

    // Returns 'true' when you reach the end of the donne (une partie de jeu se compose de plusieurs de donnes) .
    //checks that all Hands Are Empty
    bool endOfDonne();

    // Returns the winner's ID
    int getWinner() override;

    void distribution() override;

    //L'attaquant joue toujours en premier
    void playRound(int indexCardToPlay) override;

    void nextPlayer() override;

    void createCards() override;

    void startGame();

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

    static bool moveCardFromTo(vector<Card *> &srcVectOfCards, vector<Card *> &targetVectOfCards, int indexOfCard);

    // update current and final scores of players
    void updatesScores();

    // mis à jour les scores finaux des défenseurs de la donne courante
    void updateDefendersScores(float newGain);

    // Afficher les scores des autres joueurs (autre que l'attaquant de la donne qui vient de finir).
    void displayDefendersFinalScores();

    // Affiche les résultats finaux
    void displayFinalResults();

    // Affiche les résultats intermediaires
//    void displayIntermediateResults();

    // Affiche les résultats intermediaires avec des explications détatillées du comptage de points
    void displayCalculationSummary();

    // récupération de toutes les cartes (mains des joueurs + Le Chien) pour les mettre dans Deck
    void collectAllTheCards();

    void makeTheOthersPlay();

    int getIndexOfParseCard() override;

    static int getStrongestCardIndex(const vector<Card*> &listOfCards);

    float getSumOfPointsInTapis();


    // Getters and setters :

//    const vector<Card *> &getChien() const;

    void setChien(vector<Card *> &_chien);

    Player *getAttacker();

    string getName() const;

    // gagnantDuPli est toujours le 1st player
    // if gagnantDuPli = 0 then 2nd, 3rd, and 4th player are in indexes {1, 2, 3}
    // if gagnantDuPli = 1 then 2nd, 3rd, and 4th player are in indexes {2, 3, 0}
    // if gagnantDuPli = 2 then 2nd, 3rd, and 4th player are in indexes {3, 0, 1}
    // if gagnantDuPli = 3 then 2nd, 3rd, and 4th player are in indexes {0, 1, 2}
    Player *get_ith_player(int _ith);

    Player *getGagnantDuPli() const;

    void setGagnantDuPli(Player *_gagnantDuPli);

    int getIndexOfPlayer(const Player *_pPlayer);

    bool cardPlayable(Card* toPlay, const Player &concernedPlayer);

    static bool noAtoutInHand(const Player &player);

    static bool noColorInHand(COLOR expectedColor, const Player &_player);

    void print(ostream &out) override;

    int getIndexOfGagantDuPli();
};



#endif //CARD_GAMES_FRAMEWORK_TAROT_HPP
