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
    //keeps track of the turns for player allocation
    int turn = 0;
    //ignores everything in the input stream up to a newline chracter which it then clears (DONT THINK I NEED THIS ANYMORE delete limits if case)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    


    //now gets the input from the user and puts it into both inputPtr AND the toTest string
    std::getline(std::cin, *inputPtr);
    std::string toTest = *inputPtr;
    
    //if one of the regexs PASS then we allow to continue
    if(std::regex_match(toTest, replace)){
        //if the tile is able to be removed return true
        if(this->replaceTile(inputPtr)){
            std::cout << "8 TEST TEST TEST TEST\n";
            valid = true;
        }
    }

    if(std::regex_match(toTest, place)){
        //if tile canno be placed
        if(this->placeTile(inputPtr)){
            valid = true;
        }
    }      
        std::cout << "9 TEST TEST TEST TEST\n";
        return valid;
}

//everything that happens in a single player move
void GameEngine::playerMove(){

    this->printGameStatus();
 
    //gets the first attempt from the user for valid turn
    std::string input;
    std::string* inputPtr = &input;
    std::cout << "> ";
    //repeatedly ask for input until right format
    while(!this->getValidFormatMove(inputPtr)){
        std::cout << "invalid move.\nTry again\n> ";
    }
        std::cout << "10 TEST TEST TEST TEST\n";
}

//prints current board state
void GameEngine::printBoard(){

    //if anyone can do anything more elegant please do so
    std::cout << "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25\n";
    std::cout << "   ------------------------------------------------------------------------------";
    //primitive data types ;)
    char letters = 'A';
    for(int i = 0; i < MAX_MAP_LENGTH; i++){
        std::cout << "\n" << letters << " |";
        letters++;
        for(int j = 0; j < MAX_MAP_LENGTH; j++){
            if((*boardPtr)[i][j]==nullptr){
                std::cout << "  |";
            }
            else{
                Colour colour = (*boardPtr)[i][j]->getColour();
                Shape shape = (*boardPtr)[i][j]->getShape();
                std::cout << colour << shape << "|";
               }
        }
    }
    std::cout << "\n   ------------------------------------------------------------------------------";
}

//displays all game details
void GameEngine::printGameStatus(){

    std::cout << *activePlayer->getName() << ", it's your turn \n";
    std::cout << "Score for " << *player1->getName() << " " << *player1->getPoints() << "\n";
    std::cout << "Score for " << *player2->getName() << " " << *player2->getPoints() << "\n";
    this->printBoard();
    std::cout << "\nYour hand is\n";
    for(int i = 1; i <= HANDSIZE; i++){
        Tile* handTile = activePlayer->getHand()->getTile(i);
        std::cout << handTile->getColour() << handTile->getShape() << ",";
    }
    std::cout << "\n";

}

//for when the player wishes to place a tile returns false if there is a problem
bool GameEngine::placeTile(std::string* inputPtr){


    //get artive player hand as well as the bag
    playerHand = activePlayer->getHand();
    bagTiles = bag->getTiles();
    int tilePositionInHand = 0;
    bool isInHand = false;
    bool emptySpace = false;
    //CHANGE BACK TO FALSE WHEN DONE TESTING
    bool legalMove = true;
    //this next bit of code is to get the actual int for the XCOORD
    char firstDigit = (*inputPtr)[PLACE_XCOORD1];
    char secondDigit = (*inputPtr)[PLACE_XCOORD2];
    bool needSecondDigit = true;
    //if secondDigit is a space then we only need the first digit in the string
    if(secondDigit==32){
        needSecondDigit=false;
    }
    std::string inputXCoord(1,firstDigit);
    if(needSecondDigit){
        inputXCoord += secondDigit;
    }
    //string stream is used to get X coord
    std::stringstream sstream(inputXCoord);
    int xCoord = 0;
    sstream >> xCoord;
    //minusing 'A' should give us the correct coordinate 'C' - 'A' = 2 as an int, which is the correct coord
    int yCoord = (*inputPtr)[PLACE_YCOORD] - 'A';
    //check if tile is in the hand
    for(int i = 1; i <= HANDSIZE; i++){
        char colour = playerHand->getTile(i)->getColour();
        int shape = playerHand->getTile(i)->getShape();
        char colourSelect = (*inputPtr)[PLACE_COLOUR];
        //the - '0' is to convert the char to the int
        int shapeSelect = (*inputPtr)[PLACE_SHAPE] - '0';
        //to check for bool
        if(colour==colourSelect && shape==shapeSelect){
            isInHand = true;
            tilePositionInHand = i;
        }
    }
    //check if board space is empty
    if((*boardPtr)[yCoord][xCoord]==nullptr){
        emptySpace = true;
    }
    //check if board space is legal // TO DO
    //if the move is completely LEGAL
    if(isInHand && emptySpace && legalMove){
        //get from player hand and place tile on the board
        Tile* tileToPlace = playerHand->getTile(tilePositionInHand);
        (*boardPtr)[yCoord][xCoord] = tileToPlace;
        //remove from player hand
        playerHand->deleteNode(tileToPlace);
        //get a tile from the bag and place in player hand
        tileToPlace = bagTiles->getTile(0);
        playerHand->insertFront(tileToPlace);
        bagTiles->deleteFront();
        return true;

    }
    //if not legal then return false;
    return false;

}
//for when the player wishes to replace a tile in their hand returns false if there is a problem

bool GameEngine::replaceTile(std::string* inputPtr){

    //get active player hand
    playerHand = activePlayer->getHand();
    bagTiles = bag->getTiles();
    //check if tile requested exists in hand
    for(int i = 1; i < HANDSIZE + 1; i++){
        // checking to see if the tile with correct COLOUR and SHAPE exist in hand
        char colour = playerHand->getTile(i)->getColour();
        int shape = playerHand->getTile(i)->getShape();
        char colourSelect = (*inputPtr)[REPLACE_COLOUR];
        //this - '0' helps us convert the char to the accurate int
        int shapeSelect = (*inputPtr)[REPLACE_SHAPE] - '0';
        if(colour==colourSelect && shape==shapeSelect){
            std::cout << "1 TEST TEST TEST TEST\n";
            //  remove tile from hand and add to back of bag
            Tile* tile = playerHand->getTile(i);
        std::cout << "2 TEST TEST TEST TEST\n";
            bagTiles->insertBack(tile);
        std::cout << "3 TEST TEST TEST TEST\n";
            playerHand->deleteNode(tile);
        std::cout << "4 TEST TEST TEST TEST\n";
            //  remove top of bag and add to player hand
            tile = bagTiles->getTile(0);
        std::cout << "5 TEST TEST TEST TEST\n";
            playerHand->insertBack(tile);
        std::cout << "6 TEST TEST TEST TEST\n";
            bagTiles->deleteFront();
        std::cout << "7 TEST TEST TEST TEST\n";
            return true;
        }
    }
    //if no return false
    return false;       

}
