#ifndef CARD_GAMES_FRAMEWORK_UNO_HPP
#define CARD_GAMES_FRAMEWORK_UNO_HPP

#include "HuitAmericain.hpp"

class UNO : public HuitAmericain{

public:
    explicit UNO(const Deck &deck);

    void createCards() override;
    int getIndexOfParseCard() override;
};

#endif //CARD_GAMES_FRAMEWORK_UNO_HPP
