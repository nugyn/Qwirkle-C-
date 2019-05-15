#include <iostream>
#include <regex>
#include <limits>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"


class GameEngine{

    private:
    //these will all be PlayerPtrs
    Player* player1;
    Player* player2;
    Player* activePlayer;
    Bag* bag;
    //board is going to be a 2d array of tilePtrs
    TilePtr*** boardPtr; 
    void getValidFormatMove(std::string* inputPtr);
    public:
    GameEngine(Player* playerOne, Player* playerTwo, TilePtr*** boardPtr, Bag* bag);
    ~GameEngine();
    void newGame();

    };
