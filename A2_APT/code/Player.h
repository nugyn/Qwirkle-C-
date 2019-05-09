#include "LinkedList.h"

class Player{

public:
    std::string name;
    int score;
    LinkedList hand;

    Player(string name, LinkedList hand);
    ~Player();

    // Testing method, sets hand to given LinkedList
    void setHand(LinkedList hand);

    // Removes tile from hand
    void placeTile(Tile tile);
    // Adds tile to hand
    void drawTile(Tile tile);
}
