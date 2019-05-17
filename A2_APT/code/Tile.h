#ifndef TILE_H
#define TILE_H
#include "TileCodes.h"

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


private:

	Colour colour;
	Shape  shape;
};

#endif // TILE_H