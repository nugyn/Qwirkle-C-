#include "Tile.h"
#include "TileCodes.h"

Tile::Tile(Colour colourVal, Shape shapeVal)
{
	this->colour = colourVal;
	this->shape = shapeVal;
}

Tile::~Tile()
{
}

Colour Tile::getColour()
{
	return this->colour;
}

Shape Tile::getShape()
{
	return this->shape;
}

void Tile::setShape(Shape shapeVal)
{
	this->shape = shapeVal;
}

void Tile::setColour(Colour colourVal)
{
	this->colour = colourVal;
}
