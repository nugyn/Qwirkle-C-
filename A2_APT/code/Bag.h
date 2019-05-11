#pragma once
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