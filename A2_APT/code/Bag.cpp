#include "Bag.h"
#include <stdlib.h> 
#include <time.h> 


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

		linkedList.insertTile(tempTile);
	}
	shuffleBag();
}

void Bag::shuffleBag()
{
	srand(time(NULL));
	int randMax = 0;
	int randSelect = 0;

	randMax = linkedList1.size();

	while (randMax != 0)
	{
		randSelect = rand() % randMax + 1;
		linkedList2.insertTile(linkedList1.getTile(randSelect));
		linkedList1.deletePosition(randSelect);
		randMax--;
	}
}
