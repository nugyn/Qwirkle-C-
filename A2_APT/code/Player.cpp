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

Player::getTile(Colour colour, Shape shape){
  while(currNode != nullptr){

  }
}

Player::addTile(){

}

Player::replaceTile(){

}
