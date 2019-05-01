
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   // TODO
}

LinkedList::~LinkedList() {
}

void LinkedList::createTile(Colour colour, Shape shape){
   Tile* tile = new Tile(colour, shape);
   Node* temp = new Node(tile, nullptr);

		if(head == nullptr)
		{
			head = temp;
			tail = temp;
			temp = nullptr;
		}
		else
		{
			tail -> next = temp;
			tail = temp;
      }
}

   void LinkedList::insertFront(Tile* tile)
	{
		Node* insertNode = new Node(tile, nullptr);
		insertNode -> next = head;
		head = insertNode;
	}

	void LinkedList::insertPosition(int pos, Colour colour, Shape shape)
	{
		Node* pre = new Node();
		Node* cur = new Node();
		Node* temp = new Node();
		cur = head;
		for (int i = 1; i < pos; i++)
		{
			pre = cur;
			cur = cur->next;
		}
		temp ->colour = colour;
		temp->shape = shape;
		pre->next = temp;
		temp->next = cur;
	}

	void LinkedList::deletePosition(int pos)
	{
		Node* current = new Node();
		Node* previous = new Node();
		current = head;
		for (int i = 1; i < pos; i++)
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
}



}

