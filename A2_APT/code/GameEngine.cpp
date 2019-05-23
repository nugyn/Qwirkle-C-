#include "GameEngine.h"
#include <limits>
#include <iostream>


//this regex makes sure that we are getting the right format for the "place..." and "replace..."
std::regex place("(place )[ROYGBP][1-6]( at )[A-Z](2[0-5]|1[0-9]|0?[0-9])");
std::regex replace("(replace )[ROYGBP][1-6]");
//matches save followed by any character between 1 and 20 times
std::regex save("(save ).{1,20}");

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
    turnPtr = &turn;
    //ignores everything in the input stream up to a newline chracter which it then clears (DONT THINK I NEED THIS ANYMORE delete limits if case)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //while neither players hand is empty (the players hands will never be empty whilst the bag still has tiles)
    while(playerOneHand->getTile(0)!=nullptr && playerTwoHand->getTile(0)!=nullptr && !std::cin.eof()){

        this->playerMove();
        turn++;
        if(turn%2==0){
            activePlayer = player1;
        }
        else{
            activePlayer = player2;
        }
        if(!std::cin.eof()){
            std::cout << "end of turn " << turn << "\n";
        }

    }
    //The winner is declared here
    if(!std::cin.eof()){
        this->gameOver();
    }


}
//gets input and checks it is either "place <tile> at XY" OR "replace <tile>"
bool GameEngine::getValidFormatMove(std::string* inputPtr){

    //clears the cin stream
    bool valid = false;

    //now gets the input from the user and puts it into both inputPtr AND the toTest string
    std::getline(std::cin, *inputPtr);
    std::string toTest = *inputPtr;


    if(std::cin.eof()){
        valid = true;
    }

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

    if(std::regex_match(toTest, save)){
        toTest.erase(0, 5);
        std::string* fileName = &toTest;
        this->saveGame(fileName);
        valid = true;
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
    //repeatedly ask for input until right format
    while(!this->getValidFormatMove(inputPtr)){
        std::cout << "invalid move.\nTry again\n> ";
    }

}

void GameEngine::saveGame(std::string *inputFileName)
{
    IOCode *fileSaver = new IOCode();
    SaveGame *saveGame = this->convertToSaveGame();

    fileSaver->writeFile(saveGame, inputFileName);
}

SaveGame *GameEngine::convertToSaveGame()
{
    SaveGame *saveGame = new SaveGame();

    std::string *name1 = player1->getName();
    std::string *name2 = player2->getName();
    int *score1 = player1->getPoints();
    int *score2 = player2->getPoints();

    LinkedList *hand1 = player1->getHand();
    LinkedList *hand2 = player2->getHand();

    std::string hand1String = hand1->toString();
    std::string hand2String = hand2->toString();
    std::string bagString = bag->toString();

    std::string boardString = "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25\n";
    boardString += "   ------------------------------------------------------------------------------";
    //primitive data types ;)
    char letters = 'A';
    std::string stringLetter(1, letters);
    for (int i = 0; i < MAX_MAP_LENGTH; i++)
    {
        std::string stringLetter(1, letters);

        boardString += "\n" + stringLetter + " |";

        for (int j = 0; j < MAX_MAP_LENGTH; j++)
        {
            if ((*boardPtr)[i][j] == nullptr)
            {
                boardString += "  |";
            }
            else
            {
                std::string tile = (*boardPtr)[i][j]->toString();

                boardString += tile + '|';
            }
        }
        letters++;
    }
    boardString += "\n   ------------------------------------------------------------------------------";

    std::string *activePlayerString = activePlayer->getName();

    saveGame->playerName1 = *name1;

    saveGame->playerHand1 = hand1String;

    saveGame->playerScore1 = *score1;

    saveGame->playerName2 = *name2;
    saveGame->playerHand2 = hand2String;
    saveGame->playerScore2 = *score2;

    saveGame->bag = bagString;
    saveGame->board = boardString;
    saveGame->activePlayer = *activePlayerString;

    return saveGame;
}


void GameEngine::gameOver(){

    std::cout << "Game over\n";
    std::cout << "Score for " << player1->getName() << " : " << *(player1->getPoints()) << "\n";
    std::cout << "Score for " << player2->getName() << " : " << *(player2->getPoints()) << "\n";
    if(*(player1->getPoints()) > *(player2->getPoints())){
        std::cout << "Player " << player1->getName() << " won!\n";
    }
    else if(*(player2->getPoints()) > *(player1->getPoints())){
        std::cout << "Player " << player2->getName() << " won!\n";
    }
    else{
        std::cout << "Tie game, you both win! :)";
    }

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
    int handSize = activePlayer->getHand()->size();
    std::cout << "\nYour hand is\n";
    for(int i = 1; i <= handSize; i++){
        Tile* handTile = activePlayer->getHand()->getTile(i);
        std::cout << handTile->getColour() << handTile->getShape();
        if(i!=handSize){
            std::cout << ",";
        }
    }
    std::cout << "\n";

}

//for when the player wishes to place a tile returns false if there is a problem
bool GameEngine::placeTile(std::string* inputPtr){


    //get artive player hand as well as the bag
    playerHand = activePlayer->getHand();
    bagTiles = bag->getTiles();
    int points = 0;
    int* pointsPtr = &points;
    int tilePositionInHand = 0;
    bool isInHand = false;
    bool emptySpace = false;
    bool tileHasNeighbour = true;
    //CHANGE BACK TO FALSE WHEN DONE TESTING
    bool legalMoveX = false;
    bool legalMoveY = false;
    char validColourSelect = '0';
    int validShapeSelect = 0;
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
    for(int i = 1; i <= playerHand->size(); i++){
        char colour = playerHand->getTile(i)->getColour();
        int shape = playerHand->getTile(i)->getShape();
        char colourSelect = (*inputPtr)[PLACE_COLOUR];
        //the - '0' is to convert the char to the int
        int shapeSelect = (*inputPtr)[PLACE_SHAPE] - '0';
        //to check for bool
        if(colour==colourSelect && shape==shapeSelect){
            isInHand = true;
            tilePositionInHand = i;
            validColourSelect = colourSelect;
            validShapeSelect = shapeSelect;
        }
    }
    //check if board space is empty
    if((*boardPtr)[yCoord][xCoord]==nullptr){
        emptySpace = true;
    }
    //check if is not surrounded by anything and not turn 1
    if(this->noNeighboursOnY(xCoord, yCoord) && this->noNeighboursOnX(xCoord, yCoord) && ((*turnPtr)!=0)){
        tileHasNeighbour = false;
    }
    //check if board space is legal on both axis's that HAVE neighbours, if no neighbours it assumed legal (the above check accounts for if no neighbours)

    if(!this->noNeighboursOnX(xCoord, yCoord)){
        if(this->boardXAxisLegal(validColourSelect, validShapeSelect, xCoord, yCoord, pointsPtr)){
            legalMoveX = true;
        }
    }
    else{
        legalMoveX = true;
    }
    if(!this->noNeighboursOnY(xCoord, yCoord)){
        if(this->boardYAxisLegal(validColourSelect, validShapeSelect, xCoord, yCoord, pointsPtr)){
            legalMoveY = true;
        }
    }
    else{
        legalMoveY = true;
    }
    //if the move is completely LEGAL
    if(isInHand && emptySpace && legalMoveX && legalMoveY && tileHasNeighbour){
        //get from player hand and place tile on the board
        Tile* tileToPlace = playerHand->getTile(tilePositionInHand);
        (*boardPtr)[yCoord][xCoord] = tileToPlace;
        //remove from player hand
        playerHand->deletePosition(tilePositionInHand);
        //get a tile from the bag and place in player hand (if bag has tiles)
        if(bagTiles->getTile(0)!=nullptr){
            tileToPlace = bagTiles->getTile(0);
            playerHand->insertBack(tileToPlace);
            bagTiles->deleteFront();
        }
        activePlayer->addPoints(points);
        //lastly if this was the first turn of the game then the player needs to be given one point
        if((*turnPtr)==0){
            activePlayer->addPoints(1);
        }
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
    int potentialPoints = 1;
    //inserts the slected tile into list
    Tile* tilePtr = new Tile(colour, shape);
    xAxisMove->insertFront(tilePtr);
    //iterate right from input until nullptr adding to the list as we go
    while(!nullPtrFound){
        //if the tiles to the right of the space are not nullptr AND within the grid
        if(!((*boardPtr)[yInput][xInput+counter]==nullptr) && (xInput+counter < MAX_MAP_LENGTH)){
            xAxisMove->insertBack((*boardPtr)[yInput][xInput+counter]);
            potentialPoints++;
            counter++;
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
            counter++;
        }
        else{
            nullPtrFound = true;
        }
    }
    legalMove = this->checkPlacementLegality(xAxisMove);
    //if the legnth of the move was six then QWIRKLE is given
    if(xAxisMove->size()==6){
        potentialPoints += QWIRKLE;
        std::cout << "QWIRKLE!\n";
    }
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
    int potentialPoints = 1;
    //selected tile goes into list
    Tile* tilePtr = new Tile(colour, shape);
    yAxisMove->insertFront(tilePtr);
    //iterate down until a null ptr is found (adding as we go)
    while(!nullPtrFound){
        if(yInput+counter < MAX_MAP_LENGTH){
            //keep adding as long as there is a tile below that is within the grid
            if(!((*boardPtr)[yInput+counter][xInput]==nullptr)){
                yAxisMove->insertBack((*boardPtr)[yInput+counter][xInput]);
                potentialPoints++;
                counter++;
            }
            else{
                nullPtrFound = true;
            }
        }
    }
    nullPtrFound = false;
    counter = 1;
    while(!nullPtrFound){
        //had to put this check before the other as it would cause seg faults (checks if we're going outside board)
        if(yInput-counter >= 0){
            //checks if there is an empty space
            if(!((*boardPtr)[yInput-counter][xInput]==nullptr)){
                yAxisMove->insertBack((*boardPtr)[yInput-counter][xInput]);
                potentialPoints++;
                counter++;
            }
            else{
                nullPtrFound = true;
            }
        }
        else{
            nullPtrFound = true;
        }
    }
    legalMove = this->checkPlacementLegality(yAxisMove);
    //if the length was 6 then we give an additional 6 points for QWIRKLE
    if(yAxisMove->size()==6){
        potentialPoints += QWIRKLE;
        std::cout << "QWIRKLE!\n";
    }

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
    int testShape = listToTest->getTile(listToTest->size())->getShape();
    char testColour = listToTest->getTile(listToTest->size())->getColour();
    int allShapes[listToTest->size()] = {testShape};
    char allColours[listToTest->size()] = {testColour};

    //starts at 1 because we aregoing to be comparing all elements to the testColour which is based off pos 0
    for(int i = 1; i < listToTest->size(); i++){
        //check if colours are all the same
        if((listToTest->getTile(i)->getColour())!=testColour){
            allOneColour = false;

        }
        //check if shapes are all the same
        if((listToTest->getTile(i)->getShape())!=testShape){
            allOneShape = false;
        }
        allShapes[i] = listToTest->getTile(i)->getShape();
        allColours[i] = listToTest->getTile(i)->getColour();
    }
    //if all one colour then we need to confirm that all shapes are different
    if(allOneColour){
        for(int i = 0; i < listToTest->size(); i++){
            for(int j = i+1; j < listToTest->size(); j++){
                if(allShapes[j]==allShapes[i]){
                    uniqueShapes = false;
                }
            }
        }
    }
    if(allOneShape){
        for(int i = 0; i < listToTest->size(); i++){
            for(int j = i+1; j < listToTest->size(); j++){
                if(allColours[j]==allColours[i]){
                    uniqueColours = false;
                }
            }
        }
    }

    bool validityCheck = false;
    //the final check, we need either unique colours AND all one shape OR all one colour AND unique shape
    if((allOneColour && uniqueShapes) || (allOneShape && uniqueColours)){
        validityCheck = true;
    }
    if((allOneColour && allOneShape)){
        validityCheck = false;
    }
    //if its the first turn then all moves are legal
    if(*turnPtr == 0){
        validityCheck = true;
    }

    return validityCheck;

}

//for when the player wishes to replace a tile in their hand returns false if there is a problem
bool GameEngine::replaceTile(std::string* inputPtr){

    //get active player hand
    playerHand = activePlayer->getHand();
    bagTiles = bag->getTiles();
    //check if tile requested exists in hand
    for(int i = 1; i < playerHand->size() + 1; i++){
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

//just to check if the tile is on its own, returns true if TILE HAS NO NEIGHBOURS
//
//CHANGE TO ONLY CHECK ONE AXIS SO THAT IF IT DOES HAVE A NEIGHBOUR THEN U DO LEGALITY
bool GameEngine::noNeighboursOnX(int xCoord, int yCoord){

    //set to true if orientation is empty
    bool east = false;
    bool west = false;
    bool allTrue = false;

    //if it is in bounds check (checks west)
    if(xCoord-1 >= 0){
        if((*boardPtr)[yCoord][xCoord - 1]==nullptr){
            west = true;
        }
    }
    //if out of bounds then we know its not taken
    else{
        west = true;
    }
    //checks east
    if(xCoord+1 <= MAX_MAP_LENGTH){
        if((*boardPtr)[yCoord][xCoord + 1]==nullptr){
            east = true;
        }
    }
    else{
        east = true;
    }
    if(east && west){
        allTrue = true;
    }
    return allTrue;
}

bool GameEngine::noNeighboursOnY(int xCoord, int yCoord){

    bool north = false;
    bool south = false;
    bool allTrue = false;
    //checks north
    if(yCoord-1 >= 0){
        if((*boardPtr)[yCoord-1][xCoord]==nullptr){
            north = true;
        }
    }
    else{
        north = true;
    }
    //checks south
    if(yCoord+1 < MAX_MAP_LENGTH){
        if((*boardPtr)[yCoord+1][xCoord]==nullptr){
            south = true;
        }
    }
    else{
        south = true;
    }

    if(north && south){
        allTrue = true;
    }
    return allTrue;
}
