#include "Node.h"

Node::Node(Tile* tileVal, Node* nextVal)
{
	this->tile = tileVal;
	this->next = nextVal;
	this->prev = nullptr;
}

Node::Node(Tile* tileVal, Node* nextVal, Node* prevVal)
{
	this->tile = tileVal;
	this->next = nextVal;
	this->prev = prevVal;
}

Node::~Node()
{
	
}

Node* Node::getNext()
{
	return this->next;
}

Node* Node::getPrev()
{
	return this->prev;
}

void Node::setPrev(Node* prevVal)
{
	prev = prevVal;
}

void Node::setNext(Node* nextVal)
{
	next = nextVal;
}

Tile* Node::getTile()
{
	return this->tile;
}

