#include <iostream>
#include <regex>
#include <limits>
#include "Tile.h"
#include "Player.h"
#include "Bag.h"

#define HANDSIZE 6
#define REPLACE_COLOUR 8
#define REPLACE_SHAPE 9


class GameEngine{

    private:
    //these will all be PlayerPtrs
    Player* player1;
    Player* player2;
    Player* activePlayer;
    Bag* bag;
    //board is going to be a 2d array of tilePtrs
    TilePtr*** boardPtr; 
    bool getValidFormatMove(std::string* inputPtr);
    bool replaceTile(std::string* inputPtr);
    bool placeTile(std::string* inputPtr);
    void playerMove();
    void printBoard();
    void printGameStatus();
    public:
    GameEngine(Player* playerOne, Player* playerTwo, TilePtr*** boardPtr, Bag* bag);
    ~GameEngine();
    void newGame();

    };
