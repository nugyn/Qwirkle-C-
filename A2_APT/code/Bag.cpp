#include <iostream>
#include <random>
#include "Bag.h"
#include "TileCodes.h"
#include "LinkedList.h"

void Bag::fillBag()
{
	Tile* tempTile = new Tile(NULL, NULL);

	for (int i = 0; i != 72; i++)
	{
		tempTile->shape = (i % 6) + 1;

		if (i < 12)
			tempTile->colour = RED;
		if (i >= 12 && i < 24)
			tempTile->colour = ORANGE;
		if (i >= 24 && i < 36)
			tempTile->colour = YELLOW;
		if (i >= 36 && i < 48)
			tempTile->colour = GREEN;
		if (i >= 48 && i < 60)
			tempTile->colour = BLUE;
		if (i >= 60 && i < 72)
			tempTile->colour = PURPLE;

		bagArray[i] = *tempTile;
	}
	std::random_shuffle(&bagArray[0], &bagArray[72]);
	LinkedList linkedList;
	
	for (int i = 0; i < 72; i++)
	{
		linkedList.createTile(&bagArray[i]);
	}


}
