#ifndef BAG_H
#define BAG_H
#include "LinkedList.h"
#include "Tile.h"
#include <string>

class Bag
{
public:
	void fillBag();
	void shuffleBag();
	LinkedList bagLinkedList;
    LinkedList* getTiles();
	std::string toString();
private:
	LinkedList firstLinkedList;
	LinkedList secondLinkedList;
};

#endif // BAG_H
