#ifndef NODE_H
#define NODE_H
#include "Tile.h"

class Node
{
public:
	Node(Tile* tile, Node* next);
	Node(Tile* tile, Node* next, Node* prev);
	~Node();


	Node* getNext();
	Node* getPrev();
	void setPrev(Node* prev);
	void setNext(Node* next);

	Tile* getTile();


private:
	Tile* tile;
	Node* next;
	Node* prev;
};

#endif // NODE_H
