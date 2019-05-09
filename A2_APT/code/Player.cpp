#include "LinkedList.h";
#include "Player.h";

Player::Player(std::string name, LinkedList hand){
  this -> name = name;
  this -> hand = hand;
}

Player::~Player(){

}

Player::setHand(LinkedList hand){
  this -> hand = hand;
}

Player::placeTile(Colour colour, Shape shape){

}

Player::drawTile(){

}
