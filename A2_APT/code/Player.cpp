#include "Player.h";

Player::Player(std::string name){
  this -> name = name;
}

Player::Player(std::string name, LinkedList hand){
  this -> name = name;
  this -> hand = hand;
}

Player::~Player(){

}

Player::setHand(LinkedList hand){
  this -> hand = hand;
}

Player::setPoints(int points){
  this -> points = points;
}

Player::addPoints(int points){
  this -> points += points;
}

Player::getHand(){
  LinkedList* handPtr = &hand;
  return handPtr;
}

Player::getPoints(){
  int* pointsPtr = &points;
  return pointsPtr;
}

Player::getName(){
  std::string* namePtr = &name;
  return namePtr;
}

Player::addTile(Tile tile){
  hand.insertBack(tile);
}

Player::removeTile(Colour colour, Shape shape){
  return findTile(colour, shape);
}

// Moved out in case it would be needed for any other method, if not
// could move back into removeTile.
Player::findTile(Colour colour, Shape shape){
  // Don't like exit condition for this loop, will discuss a better solution
  Tile* foundTile = nullptr;
  for(int i = 1; i < hand.size(); ++i){
    Tile* tempTile = hand.getTile(i);
    if(tempTile.colour == colour && tempTile.shape == shape){
      foundTile = tempTile;
      i = hand.size();
    }
  }
  return foundTile;
}
