
#include "LinkedList.h"


LinkedList::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	// TODO
}

LinkedList::~LinkedList()
{
	clear();
}

void LinkedList::clear(){
	while (this -> head != nullptr){
		Node* toDelete = this -> head;
		head = toDelete -> next;
	}
}

int LinkedList::size(){
	
}

void LinkedList::createTile(Tile* tile)
{
	Node *temp = new Node(tile, nullptr);

	if (head == nullptr)
	{
		head = temp;
		tail = temp;
		temp = nullptr;
	}
	else
	{
		tail->next = temp;
		tail = temp;
	}
}

void LinkedList::insertFront(Tile *tile)

	if(this -> head == nullptr){
	Node *insertNode = new Node(tile, this -> head, nullptr);
	this -> head -> prev = insertNode;
	this -> head = insertNode;
	} 
	else{
	Node *insertNode = new Node(tile, this -> head, nullptr);
	this -> head -> prev = insertNode;
	this -> head = insertNode;
	}

	
	
	// else (this -> tail == nullptr){
	// 	this -> tail = insertNode;
	// }
}

void LinkedList::insertPosition(int pos, Tile* tile)
{
	Node *pre = new Node();
	Node *cur = new Node();
	Node *temp = new Node();
	cur = head;
	for (int i = 1; i < pos; i++)
	{
		pre = cur;
		cur = cur->next;
	}
	temp -> tile;
	pre -> next = temp;
	temp -> next = cur;
}

void LinkedList::insertBack(int pos, Tile* tile){

}


void LinkedList::deleteFront(){
	Node* toDelete = head;
	head = head -> next;
	head -> prev = nullptr;
	if(head == nullptr){
		// 1 in the list
		this -> tail = nullptr;
	} else {
		//...
	}

	delete toDelete;
}

void LinkedList::deletePosition(int pos)
{
	// Node *current = new Node();
	// Node *previous = new Node();
	// current = head;
	// for (int i = 1; i < pos; i++)
	// {
	// 	previous = current;
	// 	current = current->next;
	// }
	// previous->next = current->next;

	if(pos == 0){
		deleteFront();

	} else{
		// assume pos > 0
		Node* node = this -> head;
	//	Node* prev = nullptr;
		for(int count = 0; count < pos; ++count){
	//		prev = node;
			node = node -> next;
		}
	//	prev -> next = node -> next;
		delete node;
	}
}

