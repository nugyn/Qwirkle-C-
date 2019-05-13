#include "LinkedList.h"

class Player{

public:
    std::string name;
    int points;
    LinkedList hand;

    Player(std::string name);
    Player(std::string name, LinkedList hand);
    ~Player();

    // Testing method, sets hand to given LinkedList
    void setHand(LinkedList hand);

    // Returns pointer to hand
    LinkedList* getHand();

    // Returns pointer to points
    int* getPoints();

    // Returns pointer to name
    std::string* getName();

    // Adds tile to hand
    boolean addTile(Tile tile);
    // Removes tile from hand
    boolean removeTile(Tile tile);

  private:
    Tile* findTile(Tile tile);
}
