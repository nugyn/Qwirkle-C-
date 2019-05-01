
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   
   void createTile(Colour colour, Shape shape);
   void insertFront(Tile* tile);
   void insertPosition(int pos, Colour colour, Shape shape);
   void deletePosition(int pos);

private:
   Node* head;
   Node* tail;
};

#endif // ASSIGN2_LINKEDLIST_H
