#include "Player.h"

using namespace std;
Player::Player(std::string name)
{
  this->name = name;
}

Player::Player(std::string name, LinkedList* hand)
{
  this->name = name;
  this->hand = hand;
}

Player::~Player()
{
  delete namePtr;
  delete pointsPtr;
}

void Player::setHand(LinkedList* hand)
{
  this->hand = hand;
}

void Player::setPoints(int points)
{
  this->points = points;
}

void Player::addPoints(int points)
{
  this->points += points;
}

LinkedList* Player::getHand()
{
  return hand;
}

int* Player::getPoints()
{
  pointsPtr = &points;
  return pointsPtr;
}

string* Player::getName()
{
  namePtr = &name;
  return namePtr;
}

void Player::addTile(Tile* tile)
{
  if (hand -> size() == 0)
  {
    hand -> insertFront(tile);
  }
  hand -> insertBack(tile);
}

void Player::removeTile(Colour colour, Shape shape)
{
  Tile* removeTile = findTile(colour, shape);
  hand -> deleteNode(removeTile);

}

// Moved out in case it would be needed for any other method, if not
// could move back into removeTile.
Tile* Player::findTile(Colour colour, Shape shape)
{
  // Don't like exit condition for this loop, will discuss a better solution
  Tile *foundTile = nullptr;
  for (int i = 1; i < hand -> size(); ++i)
  {
    Tile *tempTile = hand -> getTile(i);
    if (tempTile -> getColour() == colour && tempTile -> getShape() == shape)
    {
      foundTile = tempTile;
      i = hand -> size();
    }
  }
  return foundTile;
}
