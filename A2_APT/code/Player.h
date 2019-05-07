#include "LinkedList.h"

class Player{

public:
    std::string name;
    int score;
    LinkedList hand;

    Player(string name);
    ~Player();

    void setHand();

    void placeTile();
    void drawTile();
}
