#include "hex.h"
#include "World.h"

using namespace std;

Hex::Hex() {

}

Hex::Hex(int q, int r) { 
	cord.setQ(q); 
	cord.setR(r);
}

Hex::Hex(int q, int r, int s) 
{
	cord.setQ(q);
	cord.setR(r);
    cord.setS(s);
}

Hex::~Hex() {

}

void Hex::setQ(int q) 
{ 
	cord.setQ(q); 
}

void Hex::setR(int r) 
{ 
	cord.setR(r); 
}

void Hex::setS(int s) 
{ 
	cord.setS(s); 
}

hexCoord Hex::getCoord() 
{ 
	return cord;
}

int Hex::getHeuristicDistance(Hex other) {
  return cord.offsetDistance(cord, other.getCoord());
}

vector<Point2D> Hex::getAdjacent(Point2D self) { 
	vector<Point2D> toReturn;

	toReturn.push_back(World::NE(self));
    toReturn.push_back(World::NW(self));
    toReturn.push_back(World::E(self));
    toReturn.push_back(World::W(self));
    toReturn.push_back(World::SE(self));
    toReturn.push_back(World::SW(self));

	return toReturn;
}