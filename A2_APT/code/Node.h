
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <memory>

class Node {
public:

  Node(Tile* tile, Node* next);
  Node(Tile* tile, Node* next, Node* prev);

 //  Node(Tile* tile, std::shared_ptr<Node> next);
 //  Node(Tile* tile,  std::shared_ptr<Node> prev);
   Node(Node& other);

   Tile*    tile;
   Node*    next;
   Node*    prev;
   bool  isHeader;

   bool setHeader();
   Node* getPrev();
   Node* getNext();
   void setNext(Node* next);
   void setPrev(Node* prev);
   bool isHeader();

  /// std::shared_ptr<Node> next;
  // std::shared_ptr<Node> prev;

            
};

#endif // ASSIGN2_NODE_H
