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

vector<Point2D> Hex::getAdjacent(int mapsize, Point2D self) { 
	vector<Point2D> toReturn;

	toReturn.push_back({self.x + 1, self.y});

	toReturn.push_back({self.x - 1, self.y});

    if (self.y % 2) 
	{
        toReturn.push_back({self.x + 1, self.y - 1});
    } 
	else 
	{
        toReturn.push_back({self.x, self.y - 1});
    }

	if (self.y % 2) 
	{
		toReturn.push_back({self.x, self.y - 1});
    }
    else 
	{
		toReturn.push_back({self.x - 1, self.y - 1});
    }

	if (self.y % 2) 
	{
        toReturn.push_back({self.x, self.y + 1});
    } 
	else 
	{
        toReturn.push_back({self.x - 1, self.y + 1});
    }
        
	if (self.y % 2) 
	{
        toReturn.push_back({self.x + 1, self.y + 1});
    } 
	else 
	{
        toReturn.push_back({self.x, self.y + 1});
    }

	return toReturn;
}