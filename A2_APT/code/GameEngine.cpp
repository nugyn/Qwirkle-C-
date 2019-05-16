#include "GameEngine.h"
#include <limits>
#include <iostream>


//this regex makes sure that we are getting the right format for the "place..." and "replace..."
std::regex place("(place )[ROYGBP][1-6]( at )[A-Z](2[0-5]|1[0-9]|0?[0-9])");
std::regex replace("(replace )[ROYGBP][1-6]");

GameEngine::GameEngine(Player* playerOne, Player* playerTwo, TilePtr*** boardPtr, Bag* bagPtr){

    this->player1 = playerOne;
    this->player2 = playerTwo;
    this->boardPtr = boardPtr;
    this->bag = bagPtr;

}
//to DO 
GameEngine::~GameEngine(){

}

void GameEngine::newGame(){

    activePlayer = player1;

    //while no players hand is empty keep getting turns
    LinkedList* playerOneHand = player1->getHand();
    LinkedList* playerTwoHand = player2->getHand();
    int turn = 0;
    while(playerOneHand->getTile(0)!=nullptr && playerTwoHand->getTile(0)!=nullptr){

        this->playerMove();
        turn++;
        if(turn%2==0){
            activePlayer = player1;
        }
        else{
            activePlayer = player2;
        }

        std::cout << "end of turn " << turn << "\n";

    }


}
//gets input and checks it is either "place <tile> at XY" OR "replace <tile>"
bool GameEngine::getValidFormatMove(std::string* inputPtr){
 
    //clears the cin stream
    bool valid = false;
    

    //ignores everything in the input stream up to a newline chracter which it then clears (DONT THINK I NEED THIS ANYMORE)
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //now gets the input from the user and puts it into both inputPtr AND the toTest string
    std::getline(std::cin, *inputPtr);
    std::string toTest = *inputPtr;
    
    //if one of the regexs PASS then we allow to continue
    if(std::regex_match(toTest, replace)){
        //if the tile is able to be removed return true
        if(this->replaceTile(inputPtr)){
            valid = true;
        }
    }
    if(std::regex_match(toTest, place)){
        //if tile canno be placed
        if(this->placeTile(inputPtr)){
            valid = true;
        }
    }
        return valid;
}

//everything that happens in a single player move
void GameEngine::playerMove(){

    this->printGameStatus();
 
    //gets the first attempt from the user for valid turn
    std::string input;
    std::string* inputPtr = &input;
    std::cout << "> ";
    this->getValidFormatMove(inputPtr);
    
    //repeatedly ask for input until right format
    while(!this->getValidFormatMove(inputPtr)){
        std::cout << "invalid move.\nTry again\n> ";
    }
}

//prints current board state
void GameEngine::printBoard(){
    
    std::cout << "BOARD HERE\n";

}

//displays all game details
void GameEngine::printGameStatus(){

    std::cout << *activePlayer->getName() << ", it's your turn \n";
    std::cout << "Score for " << *player1->getName() << " " << *player1->getPoints() << "\n";
    std::cout << "Score for " << *player2->getName() << " " << *player2->getPoints() << "\n";
    this->printBoard();
    std::cout << "\nYour hand is\n";
    for(int i = 1; i < HANDSIZE + 1; i++){
        Tile* handTile = activePlayer->getHand()->getTile(i);
        std::cout << handTile->getColour() << handTile->getShape() << ",";
    }
    std::cout << "\n";

}

//for when the player wishes to place a tile returns false if there is a problem
bool GameEngine::placeTile(std::string* inputPtr){

    return true;

}
//for when the player wishes to replace a tile in their hand returns false if there is a problem

bool GameEngine::replaceTile(std::string* inputPtr){

    //get active player hand
    std::cout << "start of replace tile\n";
    LinkedList* playerHand = activePlayer->getHand();
    LinkedList* bagTiles = bag->getTiles();
    //check if tile requested exists in hand
    for(int i = 1; i < HANDSIZE + 1; i++){
        // checking to see if the tile with correct COLOUR and SHAPE exist in hand
        char colour = playerHand->getTile(i)->getColour();
        int shape = playerHand->getTile(i)->getShape();
        char colourSelect = (*inputPtr)[REPLACE_COLOUR];
        //this - '0' helps us convert the char to the accurate int
        int shapeSelect = (*inputPtr)[REPLACE_SHAPE] - '0';

        if(colour==colourSelect && shape==shapeSelect){
            //  remove tile from hand and add to back of bag
            Tile* tile = playerHand->getTile(i);
            bagTiles->insertBack(tile);
            playerHand->deleteNode(tile);
            //  remove top of bag and add to player hand
            tile = bagTiles->getTile(0);
            playerHand->insertBack(tile);
            bagTiles->deleteNode(tile);
            return true;
        }
    }
    //if no return false
    return false;       

}
