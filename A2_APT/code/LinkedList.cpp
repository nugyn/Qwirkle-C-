#include "LinkedList.h"
#include <iostream>

//!!!!!!!!!!!!!!!!!!!!!!!
//This is a DELinked list
//!!!!!!!!!!!!!!!!!!!!!!!

LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

LinkedList::~LinkedList()
{
	clear();
}

void LinkedList::insertFront(Tile *tile) //Works
{
	Node *newNode = new Node(tile, nullptr);
	newNode->getTile()->setColour(tile->getColour());
	newNode->getTile()->setShape(tile->getShape());
	newNode->setNext(nullptr);
	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
		newNode = nullptr;
	}
	else
	{
		tail->setNext(newNode);
		tail = newNode;
	}
}

void LinkedList::insertBack(Tile *tile) //Works
{
	Node *newNode = new Node(tile, nullptr);
    newNode->setNext(nullptr);
	Node *currNode = new Node(nullptr, nullptr);
	//Node *prevNode = new Node(nullptr, nullptr);
	currNode = head;

	while (currNode->getNext() != NULL)
	{
		//prevNode = currNode;
		currNode = currNode->getNext();
	}
	//prevNode->setNext(currNode;
	currNode->setNext(newNode);
}

void LinkedList::insertPosition(int pos, Tile *tile) //Works
{
	Node *newNode = new Node(tile, nullptr);
	Node *currNode = new Node(nullptr, nullptr);
	Node *prevNode = new Node(nullptr, nullptr);
	currNode = head;

	for (int i = 1; i < pos; i++)
	{
		prevNode = currNode;
		currNode = currNode->getNext();
	}
	prevNode->setNext(newNode);
	newNode->setNext(currNode);
}

void LinkedList::deleteFront() //Works
{
	Node *toDelete = head;
	head = head->getNext();
	delete toDelete;
}

void LinkedList::deleteBack() //Works
{
	Node *currNode = new Node(nullptr, nullptr);
	Node *prevNode = new Node(nullptr, nullptr);
	currNode = head;

	while (currNode->getNext() != NULL)
	{
		prevNode = currNode;
		currNode = currNode->getNext();
	}
	tail = prevNode;
	prevNode->setNext(NULL);
	delete currNode;
}

void LinkedList::deleteNode(Tile *tile) //Works
{
	Node *currNode = new Node(nullptr, nullptr);
	Node *prevNode = new Node(nullptr, nullptr);
	currNode = head;
	Node* toDelete = new Node(nullptr, nullptr);

	while(currNode != nullptr)
	{
		if(currNode -> getTile() -> getColour() == tile -> getColour() && currNode -> getTile() -> getShape() == tile -> getShape())
		{
			toDelete = currNode;
			prevNode = currNode;
			prevNode->setNext(currNode->getNext());
			currNode = nullptr;
		}
		else
		{
			prevNode = currNode;
			currNode = currNode->getNext();
		}
	}
	delete toDelete;
}

void LinkedList::deletePosition(int pos){
	Node* currNode = new Node(nullptr,nullptr);
	Node* prevNode = new Node(nullptr, nullptr);
	currNode = head;
	if (pos == 1)
	{
		deleteFront();
		return;
	}
	for (int i = 1; i < pos; i++)
	{
		prevNode = currNode;
		currNode = currNode->getNext();
	}
	prevNode->setNext(currNode->getNext());
	delete currNode;
}

Tile* LinkedList::getTile(Tile *tile) //Works
{
	Node *currNode = nullptr;
	currNode = this->head;
	Tile *returnTile = nullptr;
	while (currNode != nullptr)
	{
		if (currNode->getTile()->getShape() == tile->getShape() && currNode->getTile()->getColour() == tile->getColour())
		{
			returnTile = currNode->getTile();
		}
		else
		{
			currNode = currNode->getNext();
		}
	}
	return returnTile;
}

Tile* LinkedList::getTile(int pos)	//Works
{
	Node* currNode = nullptr;
	currNode = this->head;
	for (int i = 1; i < pos; i++)
	{
		currNode = currNode->getNext();
	}
	return currNode->getTile();
}


void LinkedList::clear() //ERROR
{
	Node *clearNode = this->head;
	while (clearNode != nullptr)
	{
		Node *toDelete = clearNode;
		clearNode = toDelete->getNext();
		delete toDelete;
	}
	tail = nullptr;
    head = nullptr;
	delete tail;
}

int LinkedList::size() //Works
{
	int size = 0;
	Node *countNode = head;
	while (countNode != nullptr)
	{
		size++;
		countNode = countNode->getNext();
	}
	return size;
}

void LinkedList::display() //Works and for testing only
{
	Node *currNode = this->head;
	while (currNode != nullptr)
	{
		std::cout << "Colour : " << currNode->getTile()->getColour() << " Shape: " << currNode->getTile()->getShape() << "\n";
		currNode = currNode->getNext();
	}
}

std::string LinkedList::toString()
{

	std::string stringList = "";
	Node *currNode = this->head;
	while (currNode != nullptr)
	{
		stringList += currNode->getTile()->toString() + ", ";
		currNode = currNode->getNext();
	}
	return stringList;
}
