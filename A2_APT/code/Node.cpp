
#include "Node.h"

Node::Node(Tile *tile, Node* next)
{
    this->tile = tile;
    this->next = next;
}

Node::Node(Tile *tile, Node* next, Node* prev)
{
    this->tile = tile;
    this->next = next;
    this->prev = prev;
}

Node::Node(Node &other)
{
    this -> tile = other.tile;
    this -> next = other.next;
    this -> prev = other.prev;
}

//TO DO: Deconstructor
Node::~Node()
{
    delete tile;
    delete next;
}

bool Node::setHeader()
{
    this->isHeader = true;
    return true;
}

Node *Node::getPrev()
{
    return prev;
}

Node *Node::getNext()
{
    return next;
}

void Node::setNext(Node *next)
{
    next = next;
}

void Node::setPrev(Node *prev)
{
    prev = prev;
}

Tile* Node::getTile(){
    return tile;
}

