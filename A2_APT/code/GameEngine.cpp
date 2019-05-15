#include "GameEngine.h"
#include <limits>
#include <iostream>

GameEngine::GameEngine(std::string player1, std::string player2, TilePtr*** boardPtr, std::string bag){

    this->player1 = player1;
    this->player2 = player2;
    this->boardPtr = boardPtr;
    this->bag = bag;

}
//to DO 
GameEngine::~GameEngine(){

}

void GameEngine::newGame(){

    activePlayer = player1;
    //asks from player1 input
    std::string input;
    std::string* inputPtr = &input;
    std::cout << activePlayer << " please enter your move: " << std::endl;
    this->getValidFormatMove(inputPtr);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    //repeatedly ask for input until right format
    while(input.compare("-1")==0){
        std::cout << "invalid move.\nTry again: ";
        this->getValidFormatMove(inputPtr);
    }


}
//gets input and checks it is either "place <tile> at XY" OR "replace <tile>"
void GameEngine::getValidFormatMove(std::string* inputPtr){
    //this regex makes sure that we are getting the right format for the "place..."
    std::regex place("(place )[A-F][1-6]( at )[A-Z](2[0-5]|1[0-9]|0?[0-9])");
    std::regex remove("(replace )[A-F][1-6]");
    std::cin.clear();
    //ignores everything in the input stream up to a newline chracter which it then clears
    std::getline(std::cin, *inputPtr);
    if(!std::regex_match(*inputPtr, place)|| std::regex_match(*inputPtr, remove)){
        *inputPtr="-1";
    }
}







