#include "humanplayer.h"

HumanPlayer::HumanPlayer(playerName pName, GameControllerProxy _gameController)
    : Player(pName, _gameController)
{
}

void HumanPlayer::otherPlaysCard(playerName pName, const Card& playedCard)
{
    topCard = playedCard;
    emit UIplayerPlaysCard(pName, playedCard);
}

void HumanPlayer::otherDrawsCard(playerName pName)
{
    emit UIplayerDrawsCard(pName);
}

void HumanPlayer::doTurn(Card::cardSuit wishSuitCard)
{
    emit UIdoTurn(this->getPlayableCards(topCard, wishSuitCard), wishSuitCard);
}

void HumanPlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::map<playerName, int> otherPlayerCardCount, playerName startingPlayer)
{
    this->hand = hand;
    this->topCard = topCard;
    emit UIinitPlayground(hand, otherPlayerCardCount, topCard, startingPlayer);
}

void HumanPlayer::reciveCard(const Card& card)
{
    hand.push_back(card);
    emit UIaddPlayerCard(card);
}

int HumanPlayer::getCardCount() const
{
    return hand.size();
}

void HumanPlayer::UIplaysCard(const Card& card)
{
    gameController.playCard(card);
    drewCard = false;
}

void HumanPlayer::UIdoesNothing()
{
    gameController.doNothing();
    drewCard = false;
}

void HumanPlayer::UIdrawsCard()
{
    if (!drewCard) {
        gameController.drawCard();
        drewCard = true;
    } else {
        //cant draw card
    }
}
