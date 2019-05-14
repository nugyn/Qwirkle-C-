#include "Player.h";

Player::Player(std::string name){
  this -> name = name;
}

Player::~Player(){

}

Player::setHand(LinkedList* hand){
  this -> hand = *hand;
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

Player::getTile(Colour colour, Shape shape){
  return findTile(colour, shape);
}

Player::removeTile(Tile* tile){
  return findTile(colour, shape);
}

// Returns int position of tile, for use by getTile
// and removeTile.
Player::findTile(Colour colour, Shape shape){
  // Don't like exit condition for this loop, will discuss a better solution
  // for(int i = 1; i < hand.size(); ++i){
  //   Tile* tempTile = hand.getTile(i);
  //   if(tempTile.colour == colour && tempTile.shape == shape){
  //     foundTile = tempTile;
  //     i = hand.size();
  //   }
  // }
  // return foundTile;
}
