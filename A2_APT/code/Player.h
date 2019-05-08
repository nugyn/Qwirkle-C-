#include "LinkedList.h"

class Player{

public:
    std::string name;
    int score;
    LinkedList hand;

    Player(string name);
    ~Player();

    // Sets initial hand when game starts
    void setHand();

    // Removes tile from hand
    void placeTile(Tile tile);
    // Adds tile to hand
    void drawTile();
}
