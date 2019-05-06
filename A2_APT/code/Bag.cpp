#include <iostream>
#include <random>
#include "Bag.h"
#include "TileCodes.h"
#include "LinkedList.h"

void Bag::fillBag()
{
	Tile* tempTile = new Tile(NULL, NULL);

	for (int i = 0; i != 108; i++)
	{
		tempTile->shape = (i % 6) + 1;

		if (i < 18)
			tempTile->colour = RED;
		if (i >= 18 && i < 36)
			tempTile->colour = ORANGE;
		if (i >= 36 && i < 54)
			tempTile->colour = YELLOW;
		if (i >= 54 && i < 72)
			tempTile->colour = GREEN;
		if (i >= 72 && i < 90)
			tempTile->colour = BLUE;
		if (i >= 90 && i < 108)
			tempTile->colour = PURPLE;

		bagArray[i] = *tempTile;
	}
	std::random_shuffle(&bagArray[0], &bagArray[108]);
	LinkedList linkedList;
	
	for (int i = 0; i < 108; i++)
	{
		linkedList.createTile(&bagArray[i]);
	}


}
