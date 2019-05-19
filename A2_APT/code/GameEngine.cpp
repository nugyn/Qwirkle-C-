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
    //int points = 0;
    //UMCOMMENT THESE
    //int* pointsPtr = &points;
    int tilePositionInHand = 0;
    bool isInHand = false;
    bool emptySpace = false;
    //CHANGE BACK TO FALSE WHEN DONE TESTING
    bool legalMoveX = true;
    bool legalMoveY = true;
    //UNCOMMENT THESE!
    //char validColourSelect = '0';
    //int validShapeSelect = 0;
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
            //validColourSelect = colourSelect;
            //validShapeSelect = shapeSelect;
        }
    }
    //check if board space is empty
    if((*boardPtr)[yCoord][xCoord]==nullptr){
        emptySpace = true;
    }
    //UNCOMMENT THESE
    //check if board space is legal
    //if(this->boardXAxisLegal(validColourSelect, validShapeSelect, xCoord, yCoord, pointsPtr)){
    //    legalMoveX = true;
    //}
    //if(this->boardYAxisLegal(validColourSelect, validShapeSelect, xCoord, yCoord, pointsPtr)){
    //    legalMoveY = true;
    //}


    //if the move is completely LEGAL
    if(isInHand && emptySpace && legalMoveX && legalMoveY){
        //get from player hand and place tile on the board
        Tile* tileToPlace = playerHand->getTile(tilePositionInHand);
        (*boardPtr)[yCoord][xCoord] = tileToPlace;
        //remove from player hand
        playerHand->deletePosition(tilePositionInHand);
        //get a tile from the bag and place in player hand
        tileToPlace = bagTiles->getTile(0);
        playerHand->insertBack(tileToPlace);
        bagTiles->deleteFront();
        return true;

    }
    //if not legal then return false;
    return false;

}
// checks the legality along the X Axis
bool GameEngine::boardXAxisLegal(char colour, int shape, int xInput, int yInput, int* points){

    LinkedList* xAxisMove = new LinkedList();
    bool nullPtrFound = false;
    bool legalMove = false;
    int counter = 1;
    int potentialPoints = 0;
    //inserts the slected tile into list
    Tile* tilePtr = new Tile(colour, shape);
    xAxisMove->insertBack(tilePtr);
    //iterate right from input until nullptr adding to the list as we go
    while(!nullPtrFound){
        //if the tiles to the right of the space are not nullptr AND within the grid
        if(!((*boardPtr)[yInput][xInput+counter]==nullptr) && (xInput+counter <= MAX_MAP_LENGTH)){
            xAxisMove->insertBack((*boardPtr)[yInput][xInput+counter]);
            potentialPoints++;
        }
        else{
            nullPtrFound = true;
        }
    }
    nullPtrFound = false;
    counter = 1;
    while(!nullPtrFound){
        //if the tiles to the left of the space are not nullptr AND within the grid
        if(!((*boardPtr)[yInput][xInput-counter]==nullptr) && (xInput-counter >= 0)){
            xAxisMove->insertBack((*boardPtr)[yInput][xInput-counter]);
            potentialPoints++;
        }
        else{
            nullPtrFound = true;
        }
    }  

    legalMove = this->checkPlacementLegality(xAxisMove);
    //if it was a legal move update points
    if(legalMove){
        *points+=potentialPoints;
    }

    delete xAxisMove;
    return legalMove;

}
//checks the legality down the y axis
bool GameEngine::boardYAxisLegal(char colour, int shape, int xInput, int yInput, int* points){

    LinkedList* yAxisMove = new LinkedList();
    bool nullPtrFound = false;
    bool legalMove = false;
    int counter = 1;
    int potentialPoints = 0;
    //selected tile goes into list
    Tile* tilePtr = new Tile(colour, shape);
    yAxisMove->insertBack(tilePtr);
    //iterate down until a null ptr is found (adding as we go)
    while(!nullPtrFound){
        //keep adding as long as there is a tile below that is within the grid
        if(!((*boardPtr)[yInput+counter][xInput]==nullptr) && (yInput+counter <= MAX_MAP_LENGTH)){
            yAxisMove->insertBack((*boardPtr)[yInput+counter][xInput]);
            potentialPoints++;
        }
        else{
            nullPtrFound = true;
        }
    }
    nullPtrFound = false;
    counter = 1;
    while(!nullPtrFound){
        if(!((*boardPtr)[yInput-counter][xInput]==nullptr) && (yInput-counter >= 0)){
            yAxisMove->insertBack((*boardPtr)[yInput-counter][xInput]);
            potentialPoints++;
        }
        else{
            nullPtrFound = true;
        }
    }
    legalMove = this->checkPlacementLegality(yAxisMove);
    if(legalMove){
        *points+=potentialPoints;
    }
    delete yAxisMove;
    return legalMove;

}

bool GameEngine::checkPlacementLegality(LinkedList* listToTest){


    bool allOneColour = true;
    bool allOneShape = true;
    bool uniqueColours = true;
    bool uniqueShapes = true;
    char testShape = listToTest->getTile(0)->getShape();
    int testColour = listToTest->getTile(0)->getColour();
    char allShapes[listToTest->size()+1] = {testShape}; 
    int allColours[listToTest->size()+1] = {testColour};
    
    for(int i = 1; i < listToTest->size()+1; i++){
        //check if colours are all the same
        if(!((listToTest->getTile(i)->getColour())==testColour)){
            allOneColour = false;

        }
        //check if shapes are all the same
        if((!listToTest->getTile(i)->getShape())==testShape){
            allOneShape = false;
        }
        allShapes[i] = listToTest->getTile(i)->getShape();
        allColours[i] = listToTest->getTile(i)->getColour();
    }
    //if all one colour then we need to confirm that all shapes are different
    if(allOneColour){
        for(int i = 0; i < listToTest->size()+1; i++){
            for(int j = i; j < listToTest->size()+1; j++){
                if(allShapes[j]!=allShapes[i]){
                    uniqueShapes = false;
                }
            }
        }
    }
    if(allOneShape){
        for(int i = 0; i < listToTest->size()+1; i++){
            for(int j = i; j < listToTest->size()+1; j++){
                if(allColours[j]!=allColours[i]){
                    uniqueColours = false;
                }
            }
        }
    }

    //the final check, we need either unique colours AND all one shape OR all one colour AND unique shape
    if((allOneColour && uniqueShapes) || (allOneShape && uniqueColours)){
        return true;
    }
    else{
        return false;
    }

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
            //  remove tile from hand and add to back of bag
            Tile* tile = playerHand->getTile(i);
            bagTiles->insertBack(tile);
            playerHand->deletePosition(i);
            //  remove top of bag and add to player hand
            tile = bagTiles->getTile(0);
            playerHand->insertBack(tile);
            bagTiles->deleteFront();
            return true;
        }
    }
    //if no return false
    return false;       

}
