#ifndef BAG_H
#define BAG_H
#include "LinkedList.h"

class Bag
{
public:
	void fillBag();
	void shuffleBag();
	LinkedList bagLinkedList;
private:
	LinkedList firstLinkedList;
	LinkedList secondLinkedList;
};

#endif //BAG_H