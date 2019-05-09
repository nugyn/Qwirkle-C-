#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include "Bag.h"
#include "TileCodes.h"
#include "LinkedList.h"

void Bag::fillBag()
{
	LinkedList linkedList;
	LinkedList randLinkedList;
    Tile* tempTile = new Tile(NULL, NULL);
	int randMax = 0;
	int randSelect = 0;
	srand(time(NULL));
	
	
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

		linkedList.insertTile(tempTile);
	}
	
	randMax = linkedList.size();
	
	while (randMax != 0)
	{
		randSelect = rand() % randMax + 1;
		randLinkedList.insertTile(linkedList.getTile(randSelect));
		linkedList.deletePosition(randSelect);
		randMax--;
	}


}

void Bag::shuffleBag()
{
}
