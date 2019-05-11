#include "LinkedList.h"

class Player{

public:
    std::string name;
    int score;
    LinkedList hand;

    Player(std::string name);
    Player(std::string name, LinkedList hand);
    ~Player();

    // Testing method, sets hand to given LinkedList
    void setHand(LinkedList hand);

    // Removes tile from hand
    boolean getTile(Tile tile);
    // Adds tile to hand
    boolean addTile(Tile tile);
  private:
    Node currNode;
}
