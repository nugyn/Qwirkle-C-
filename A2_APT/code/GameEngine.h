#include <iostream>
#include <regex>
#include <limits>
#include "Tile.h"


class GameEngine{

    private:
    //these will all be PlayerPtrs
    std::string player1;
    std::string player2;
    std::string activePlayer;
    std::string bag;
    //board is going to be a 2d array of tilePtrs
    TilePtr*** boardPtr; 
    void getValidFormatMove(std::string* inputPtr);
    public:
    GameEngine(std::string player1, std::string player2, TilePtr*** boardPtr, std::string bag);
    ~GameEngine();
    void newGame();

    };
