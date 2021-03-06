#include "player.h"
#include <algorithm>
#include <stdexcept>

PLAYER::Name Player::getPName() const
{
    return playerName;
}

int Player::getCardCount() const
{
    return this->hand.size();
}

std::string Player::getTitle() const
{
    return title;
}

Player::Player(PLAYER::Name pName, GameControllerProxy _gameController, std::string title)
    : playerName(pName)
    , gameController(_gameController)
    , title(title)
{
}

Player::~Player()
{

}

std::vector<Card> Player::getPlayableCards(const Card& card, Card::cardSuit wishedSuit)
{
    std::vector<Card> playableCards;
    for (unsigned i = 0; i < hand.size(); ++i) {
        if (card.getValue() == wishSuitCard) {
            //in case a wishSuitCard is on top at game start
            if (wishedSuit == Card::NONE && (card.getValue() == hand[i].getValue() || card.getSuit() == hand[i].getSuit())) {
                playableCards.push_back(hand[i]);
            } else if (card.getValue() == hand[i].getValue() || wishedSuit == hand[i].getSuit()) {
                playableCards.push_back(hand[i]);
            }
        } else {
            if (card.getValue() == hand[i].getValue() || card.getSuit() == hand[i].getSuit() || hand[i].getValue() == wishSuitCard) {
                playableCards.push_back(hand[i]);
            }
        }
    }
    return playableCards;
}

void Player::dropCard(const Card& card)
{
    std::vector<Card>::iterator pos = std::find(hand.begin(), hand.end(), card);

    if (pos != hand.end()) {
        hand.erase(pos);
    } else {
        throw std::range_error("Card not found in hand.");
    }
}
