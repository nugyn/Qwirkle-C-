#include "LinkedList.h"

class Player{

public:
    std::string name;
    int points;
    LinkedList hand;

    Player(std::string name);
    ~Player();

    // Testing method, sets hand to given LinkedList
    void setHand(LinkedList hand);
    // Sets player score to given value
    void setPoints(int points);
    // Increases player score by given value
    void addPoints(int points);

    // Returns pointer to hand
    LinkedList* getHand();

    // Returns pointer to points
    int* getPoints();

    // Returns pointer to name
    std::string* getName();

    // Adds tile to hand
    void addTile(Tile tile);
    // Returns pointer to tile with corresponding colour
    // and shape. Could use hash for quick check?
    Tile* getTile(Colour color, Shape shape);
    // Removes tile from hand
    void removeTile(Tile* tile);

  private:
    Tile* findTile(Tile tile);
}
