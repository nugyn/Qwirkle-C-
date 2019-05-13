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

Player::addTile(Tile tile){
  hand.insertBack(tile);
}

Player::removeTile(Colour colour, Shape shape){
  hand.findTile(colour, shape);
}

Player::findTile(Colour colour, Shape shape){
  // Don't like exit condition for this loop, will discuss a better solution
  Tile* foundTile;
  for(int i = 1; i < hand.size(); ++i){
    Tile* tempTile = hand.getTile(i);
    if(tempTile.colour == colour && tempTile.shape == shape){
      foundTile = &tempTile;
      i = hand.size();
    }
  }
  return foundTile;
}
