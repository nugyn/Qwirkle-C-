#ifndef TILE_H
#define TILE_H

#include "TileCodes.h"
#include <string>
#include <sstream>
#include <iostream>

typedef char Colour;
typedef int Shape;

class Tile
{
public:

	Tile(Colour colour, Shape shape);
	~Tile();

	Colour getColour();
	Shape getShape();
	void setColour(Colour colour);
	void setShape(Shape shape);
	std::string toString();


private:

	Colour colour;
	Shape  shape;
};

#endif // TILE_H
