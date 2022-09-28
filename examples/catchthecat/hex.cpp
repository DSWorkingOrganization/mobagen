#include "hex.h"

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

hexCoord Hex::getCoord() 
{ 
	return cord;
}

int Hex::getHeuristicDistance(Hex other) {
  return cord.offsetDistance(cord, other.getCoord());
}

vector<Point2D> Hex::getAdjacent(int mapsize) { 
	vector<Point2D> toReturn;
	return toReturn;
}