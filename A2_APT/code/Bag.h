#pragma once
#include "LinkedList.h"

class Bag
{
public:
	void fillBag();
	void shuffleBag();
private:
	LinkedList linkedList1;
	LinkedList linkedList2;
};