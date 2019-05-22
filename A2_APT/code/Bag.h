#ifndef BAG_H
#define BAG_H

#include "LinkedList.h"
#include "Tile.h"

class Bag
{
public:
	void fillBag();
	void shuffleBag();
	LinkedList bagLinkedList;
    LinkedList* getTiles();
private:
	LinkedList firstLinkedList;
	LinkedList secondLinkedList;
};

#endif // BAG_H
