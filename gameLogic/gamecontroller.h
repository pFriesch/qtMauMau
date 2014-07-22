#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <stdexcept>
#include <vector>
#include "deck.h"

#include "player.h"
#include "PlayerNames.h"
#include "card.h"

class GameController {

private:
    std::vector<Player*> players;
    //The stack of cards where cards are taken if a player has to draw.
    Deck cardStack;
    //The stack of cards where the played cards are dropped.
    Deck cardDepot;

    //flags
    int playerCount;
    //default start player is 0

    //every turn flags
    playerName currentPlayer;
    bool changedDirection = false;
    Card::cardSuit wishedSuit = Card::cardSuit(0);
    bool draw2x = false;
    int draw2xCount = 0;
    bool skipNextPlayer = false;
    //TODO always 4 players, 4+ players unregarded
    bool currentPlayerDrewCard = false;
    bool currentPlayerPlayedCard = false;

    //special cards
    bool withDraw2xCard = true;
    const Card::cardValue draw2xCard = Card::SEVEN;
    bool withWishedSuit = true;
    const Card::cardValue wishSuitCard = Card::JACK;
    bool withSkipPlayer = true;
    const Card::cardValue skipNextCard = Card::EIGHT;
    bool withChangeDirection = false;
    const Card::cardValue changeDirectCard = Card::TEN;

public:
    explicit GameController(playerName currentPlayer = BOTTOM, int playerCount = 4);
    void gameInit();

    void playCard(playerName pName, const Card& card, Card::cardSuit whishedSuit);
    void drawCard(playerName pName);
    void doNothing(playerName pName);

    Player* getBottomPlayer();

    //    void otherPlaysCard(playerName pName, const Card& playedCard);
    //    void otherDrawsCard(playerName pName);

private:
    void nextTurn();
    void setFlags(const Card& card);
    void setNextPlayer();
    void otherPlayerDrawsCard(playerName pName);
    void otherPlayerPlaysCard(playerName pName, const Card& card);
};

#endif // GAMECONTROLLER_H
