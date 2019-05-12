#pragma once
#include "Node.h"

class LinkedList
{

public:
	LinkedList();
	~LinkedList();

	void insertFront(Tile* tile);	
	void insertBack(Tile* tile);
	void insertPosition(int pos, Tile* tile);

	void deleteFront();
	void deleteBack();
	void deletePosition(int pos);

	Tile* getTile(int pos);
	void clear();
	int size();
	void display();



private:
	Node* head;
	Node* tail;
};