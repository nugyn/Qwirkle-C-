#include "Bag.h"
#include <time.h>
#include <stdlib.h>

void Bag::fillBag()
{
	for (int i = 0; i < 72; i++)
	{
		Tile* tempTile = new Tile('R', 1);
		tempTile->setShape((i % 6) + 1);

		if (i < 12)
			tempTile->setColour(RED);
		if (i >= 12 && i < 24)
			tempTile->setColour(ORANGE);
		if (i >= 24 && i < 36)
			tempTile->setColour(YELLOW);
		if (i >= 36 && i < 48)
			tempTile->setColour(GREEN);
		if (i >= 48 && i < 60)
			tempTile->setColour(BLUE);
		if (i >= 60 && i < 72)
			tempTile->setColour(PURPLE);

		firstLinkedList.insertFront(tempTile);
	}
	shuffleBag();
}

void Bag::shuffleBag()
{
	if (firstLinkedList.size() != 0)
	{
		int randSelect = 0;
		int randMax = firstLinkedList.size();
		srand(time(NULL));
		while (randMax != 0)
		{
			randMax = firstLinkedList.size();
			randSelect = rand() % randMax + 1;
			secondLinkedList.insertFront(firstLinkedList.getTile(randSelect));
			firstLinkedList.deletePosition(randSelect);
			randMax--;
		}
		bagLinkedList = secondLinkedList;
	}
	else
	{
		int randSelect = 0;
		int randMax = secondLinkedList.size();
		srand(time(NULL));
		while (randMax != 0)
		{
			randMax = secondLinkedList.size();
			randSelect = rand() % randMax + 1;
			firstLinkedList.insertFront(secondLinkedList.getTile(randSelect));
			secondLinkedList.deletePosition(randSelect);
			randMax--;
		}
		bagLinkedList = firstLinkedList;
	}
}
LinkedList* Bag::getTiles(){

    LinkedList* tilesPtr = new LinkedList();
    tilesPtr = &bagLinkedList;
    return tilesPtr;

}

std::string Bag::toString(){
	LinkedList *bagList = &(bagLinkedList);
	std::string bagString = bagList -> toString();
	return bagString;
}
