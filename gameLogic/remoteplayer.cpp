#include "remoteplayer.h"

RemotePlayer::RemotePlayer(Server* server, int playerId)
{
}

void RemotePlayer::otherPlaysCard(int playerId, const Card& playedCard)
{
}

void RemotePlayer::otherDrawsCard(int playerId)
{
}

void RemotePlayer::doTurn()
{
}

void RemotePlayer::gameInit(const std::vector<Card>& hand, const Card& topCard, std::vector<int> otherPlayerCardCount, int playerId)
{
}

void RemotePlayer::reciveCard(const Card& card)
{
}

int RemotePlayer::getCardCount() const
{
}
