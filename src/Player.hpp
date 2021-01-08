#ifndef CARD_GAMES_FRAMEWORK_PLAYER_HPP
#define CARD_GAMES_FRAMEWORK_PLAYER_HPP


#include <string>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"


using namespace std;

class Player {

private:
    const int unique_id;
    string name;
    vector<Card *> hand;
    vector<Card *> reserve;

    // score intermediaire (calculé pour chaque donne)
    int current_score;

    // score final calculé à partir des scores intermediaires de chaque donne
    int final_score;

    // Used by the get_fresh_player_uid() method to generate unique IDs
    static int player_id_counter;

    // Generates a new identifier for each call that is different from the previous ones returned.
    static int get_fresh_player_uid();

public:

    // Ctor
    Player(int _uid, const string &_name, const vector<Card *> &_hand, int _score = 0);

    // copy ctor
    Player(const Player &player);

    // Dtor
    virtual ~Player();

    //Getters :

    int getUniqueId() const;

    const string &getName() const;

    vector<Card *> &getHand();

    int getCurrentScore() const;

    int getFinalScore() const;

    vector<Card *> getReserve() const;

    int getIndexOfCardToPlay();
    // Setters :

    void setCurrentScore(float _score);

    void setHand(const vector<Card *> &_hand);

    void setReserve(const vector<Card *> &_reserve);

    // Other methods :

    bool handEmpty();

    //todo : Player::playCard(arg) : il faut se mettre d'accord si on passe l'index ou l'ID en arg
    Card *playCard(int index);

    // ajoute la carte (au fait c'est son pointeur) passée en argument à la main du joueur courant
    void addCard(Card *toAdd);

    void displayHand() const;

    // Remettre les cartes de la main du joueur courant dans le Deck passé en arg
    // (ça sert à remélanger et redistribuer par e.g)
    void putBackHand(Deck &_deck);

    // Remettre les cartes qui sont dans la réserve (cartes gagnées) du joueur courant dans le Deck passé en arg
    // (ça sert à remélanger et redistribuer par e.g)
    void putBackReserve(Deck &_deck);

    void setFinalScore(int finalScore);

};

/// Surcharge de l’opérateur <<
std::ostream &operator<<(std::ostream &out, const Player &a_game);

#endif //CARD_GAMES_FRAMEWORK_PLAYER_HPP
