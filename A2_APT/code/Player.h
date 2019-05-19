#ifndef PLAYER_H
#define PLAYER_H

#include "LinkedList.h"
#include <string>
#include <iostream>
#include "LinkedList.h"


using namespace std;

class Player{

public:
    std::string name;
    int points;
    LinkedList* hand;

    Player(std::string name);
    Player(std::string name, LinkedList* hand);
    ~Player();

    // Testing method, sets hand to given LinkedList
    void setHand(LinkedList* hand);
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
    void addTile(Tile * tile);
    // Gets tile from hand
    Tile* getTile(Colour color, Shape shape);
    // Removes tile from hand
    void removeTile(Colour colour, Shape shape);

  private:
    Tile* findTile(Colour colour, Shape shape);
};

#endif // PLAYER_H
