
#include "Node.h"

Node::Node(Tile *tile, Node *next)
{
    this->tile = tile;
    this->next = next;
}

Node::Node(Tile *tile, Node *next, Node *prev)
{
    this->tile = tile;
    this->next = next;
    this->prev = prev;
}

//TO DO: Deconstructor
Node::Node(Node &other)
{
    // TO DO
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

bool Node::isHeader()
{
    return isHeader;
}
