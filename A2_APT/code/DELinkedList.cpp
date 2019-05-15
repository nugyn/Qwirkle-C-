
#include "LinkedList.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
}

LinkedList::~LinkedList()
{
	clear();
}

LinkedList::LinkedList(LinkedList &other){
	Node * copyNode = other.head;
	while(copyNode != nullptr)
	{
		insertTile(copyNode -> getTile());
		copyNode = copyNode -> getNext();
	}
}

void LinkedList::clear()
{
	Node* clearNode = head;
	while (clearNode != nullptr)
	{
		Node *toDelete = clearNode;
		clearNode = toDelete->getNext();
		delete toDelete;
	}
	tail = nullptr;
	delete tail;
}

int size(Node* node){
	int retVal = 0;
		if(node == nullptr){
			retVal = 0;
		}
		else {
			retVal = 1 + size(node -> next)
		}
		return retVal;
}

int LinkedList::size()
{	
	return size(head);
	//Size(n) = 1 + Size(small h)
    //Size(empty) = 0
	// int retVal = 0;
	// if( head = nullptr){
	// 	retVal = 0;
	// }
	// else {
	// 	retVal = 1 + size(head -> next)
	// }
	// return retVal;


		/*
	int size = 0;
	Node *countNode = this->head;
	while (countNode != nullptr)
	{
		size++;
		countNode = countNode->getNext();
	}
	return size;
	*/
}

void LinkedList::insertTile(Tile *tile)
{
	Node *newNode = new Node(tile, nullptr, nullptr);
	Node *currNode = this->head;

	if (currNode == nullptr)
	{
		head = newNode;
		tail = newNode;
		newNode->setNext(nullptr);
		newNode->setPrev(nullptr);
	}
	else
	{
		while (currNode->getNext() != nullptr)
		{
			if (currNode->getNext() == nullptr)
			{
				currNode->setNext(newNode);
				tail = newNode;
				tail->setNext(nullptr);
				tail->setPrev(currNode);
			}
		}
	}
}

void LinkedList::insertFront(Tile *tile)
{

	if (this->head == nullptr)
	{
		Node *insertNode = new Node(tile, nullptr, nullptr);
		this->head = insertNode;
	}
	else
	{
		Node *insertNode = new Node(tile, this->head, nullptr);
		Node *currNode = head;
		currNode->setNext(currNode);   // change the reference to the next node of head to the currentHead
		currNode->setPrev(insertNode); // change the previous of Head to the newNode
		this->head = insertNode;	   //the new head is now insertNode.
	}
}

void LinkedList::insertPosition(int pos, Tile *tile)
{
	Node *currNode = head; //pos
	Node *preNode = nullptr;
	Node *insertNode = new Node(tile, nullptr, nullptr);
	for (int i = 1; i < pos; i++)
	{
		preNode = currNode;
		currNode = currNode->getNext();
	}
	preNode->setNext(insertNode);  // previous to end, then setNext, to the one being inserted
	insertNode->setNext(currNode); // the the inserted node, setNext to the currNode of pos.
	insertNode->setPrev(preNode);  // the previous of insert needs to be preNode
}

Node* LinkedList::insertBack(Tile *tile)
{
	Node* newHead = nullptr;
		if(newHead == nullptr){
			newHead = new Node(tile, nullptr);
		}
		else{
			newHead -> next = insertBack(node -> next, data);
			newHead = node;
		}

	return newHead;
	// Node *insertNode = new Node(tile, nullptr, nullptr); // node to be inserted
	// Node *backNode = this -> tail; // the end node, which is the tail
	// backNode -> setNext(insertNode); //reassign the next node to be the inserted node
	// insertNode -> setPrev(backNode); // set previous of the inserted to the previous end node
	// insertNode -> setNext(nullptr); // set the next of inserted node to nyll
	// this -> tail = insertNode;  //re assign to tail 
}

void LinkedList::insertBack(Node* node, Tile* tile){
		insertBack(node, tile);
}

void LinkedList::deleteBack()
{
	Node *toDelete = this->tail;
	Node *newTail = this->tail;

	newTail = newTail->getPrev();

	delete toDelete;

	this->tail = newTail;
}

void LinkedList::deleteFront()
{
	Node *toDelete = head;

	if (head == nullptr)
	{
		// 1 in the list
		this->tail = nullptr;
	}
	else
	{
		head = head -> getNext();
		head -> setPrev(nullptr);
	}

	delete toDelete;
}

void LinkedList::deletePosition(int pos)
{
	Node *currNode = nullptr;
	Node *prevNode = nullptr;
	currNode = this->head;
	for (int i = 1; i < pos; i++)
	{
		if (pos == 1)
		{
			deleteFront();
			return;
		}
		prevNode = currNode;
		currNode = currNode -> getNext();
	}
	prevNode -> setNext(currNode -> getNext());
	delete currNode;
}

string LinkedList::printList(){

	Node* currNode = this -> head;
	while (currNode != nullptr)
	{

		Tile* tile = currNode -> getTile();
		currNode = currNode -> getNext();
	
		//cout << 
	}


}