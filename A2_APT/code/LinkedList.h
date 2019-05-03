
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include <memory>
#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int size();
   void clear();
   void createTile(Tile* tile);

   void insertFront(Tile* tile);
   void insertPosition(int pos, Tile* tile);
   void insertBack(Tile* tile);

   void deleteFront();
   void deleteBack();
   void deletePosition(int pos);

private:
   Node* head;
   Node* tail;

   //std::shared_ptr<Node> head;
   //std::shared_ptr<Node> tail;
};

#endif // ASSIGN2_LINKEDLIST_H
