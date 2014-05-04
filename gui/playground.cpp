#include <QImage>
#include <QBrush>
#include <QGraphicsItem>
#include <QDebug>
#include <QMouseEvent>
#include "gui\playground.h"

Playground::Playground(QObject* parent)
    : QGraphicsScene(parent)
{
    QImage img("img/green_background.jpg", "jpg");
    cardWidth = 71;
    cardHeight = 96;
    QBrush brush(img);
    this->setBackgroundBrush(brush);
}

void Playground::measureLayout()
{
    //Center for the scene, but we need to include the card sizes
    QPointF sceneCenterPointRaw = this->sceneRect().center();
    //The real center for a Card
    qreal sceneCenter_X = sceneCenterPointRaw.x() - cardWidth;
    qreal sceneCenter_Y = sceneCenterPointRaw.y() - cardHeight;

    layout.insert("STACK_X", sceneCenter_X);
    layout.insert("STACK_Y", sceneCenter_Y);

    layout.insert("TALON_X", sceneCenter_X + cardWidth + 20);
    layout.insert("TALON_Y", sceneCenter_Y);

    int playerCardsWidth = ((humanPlayerCards->size()) * horizontalCardGap);
    layout.insert("HUMAN_X", ((sceneCenterPointRaw.x()) - (playerCardsWidth / 2)));
    layout.insert("HUMAN_Y", height() - cardHeight - 30);
}

void Playground::startGame()
{

    fakeInit();

    CardItem* stack = new CardItem(CardItem::specialCards::RED_VERTICAL);
    stack->getGraphicsItem()->setPos(layout.value("STACK_X"), layout.value("STACK_Y"));
    cardItems.append(stack);
    this->addItem(stack->getGraphicsItem());

    CardItem* talon = new CardItem(CardItem::specialCards::TALON);
    talon->getGraphicsItem()->setPos(layout.value("TALON_X"), layout.value("TALON_Y"));
    talon->getGraphicsItem()->setOpacity(0.7);
    cardItems.append(talon);
    this->addItem(talon->getGraphicsItem());
}

void Playground::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->buttonDownScenePos(event->button()), QTransform());
    if (item == NULL) {
        // do stuff if not clicked on an item
    } else {

        //signal to GameController
        // QGraphicsScene::mousePressEvent(event); // this forwards the event to the item
    }
}

//bekomme alle Karten und anzahl karten der anderen Mitspieler
// topDepotCard kann ja auch keine sein also NULL, vielleicht doch lieber POINTER!!! TODO
void Playground::initPlayground(QVector<Card>* humanPlayerCards, QVector<short> otherPlayerCardCount, Card* topDepotCard, short startingPlayer)
{
    this->humanPlayerCards = humanPlayerCards;
    this->otherPlayerCardCount = otherPlayerCardCount;

    measureLayout();

    for (int i = 0; i < humanPlayerCards->size(); i++) {
        CardItem* card = new CardItem(humanPlayerCards->at(i));
        card->getGraphicsItem()->setPos(layout.value("HUMAN_X"), layout.value("HUMAN_Y"));
        layout.insert("HUMAN_X", layout.value("HUMAN_X") + horizontalCardGap);
        this->addItem(card->getGraphicsItem());
    }

    PlayerItem p(PlayerItem::direction::LEFT, 5, this->sceneRect().center());

    //there are alway 3 other player
    for (int i = 0; i < otherPlayerCardCount.size(); ++i) {
        for (int j = 0; j < p.getCards().size(); ++j) {
            this->addItem(p.getCards().at(j)->getGraphicsItem());
        }
    }
}

// bekomme alle Spielbaren Karten von Human player
void Playground::playerDoTurn(QVector<Card>* playableCards)
{
}

// Spieler spielt eine Karte und welche
void Playground::playerPlaysCard(short player, Card& playedCard)
{
}

// Spieler zieht eine Karte
void Playground::playerDrawsCard(short player, Card& card)
{
}

// Human Spieler hat eine Karte gezogen
void Playground::addPlayerCard(const Card& card)
{
}

/**
  * That are allllll fake methods
  *
 * @brief Playground::fakeInit
 */
void Playground::fakeInit()
{
    QVector<short> otherPlayerCardCount = QVector<short>();
    for (int i = 0; i < 4; i++) {
        otherPlayerCardCount += 5;
    }

    QVector<Card>* cards = new QVector<Card>();
    cards->append(Card(Card::cardSuit::CLUBS, Card::cardValue::ACE));
    cards->append(Card(Card::cardSuit::CLUBS, Card::cardValue::KING));
    cards->append(Card(Card::cardSuit::DIAMONDS, Card::cardValue::SEVEN));
    cards->append(Card(Card::cardSuit::HEARTS, Card::cardValue::TEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));
    cards->append(Card(Card::cardSuit::SPADES, Card::cardValue::QUEEN));
    short i = 2;
    Card* c = new Card(Card::cardSuit::SPADES, Card::cardValue::ACE);
    this->initPlayground(cards, otherPlayerCardCount, c, i);
}
