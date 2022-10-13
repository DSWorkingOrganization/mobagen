#include "node.h"
#include "World.h"
#include <stdexcept>

using namespace std;

Node::Node() 
{ 
	//poin = Point2D(0, 0); 
	hexa = {poin.x, poin.y};
}

Node::Node(Point2D pos) 
{ 
	poin = pos; 
	hexa = {poin.x, poin.y};
}

Node::~Node() {

}

void Node::setPoint(Point2D pos) { 
	poin = pos; 
}

void Node::setAWeight(int weight) { 
	accumulatedWeight = weight; 
}

void Node::setHWeight(Point2D destination, int worldSize) {
  heuristicWeight = min(worldSize - abs(poin.x), worldSize - abs(poin.y));
}

void Node::setVisted(bool visited) { 
	visit = visited;
}

void Node::setWall(bool wall) { 
	isWall = wall; 
}

Point2D Node::getPos() { 
	return poin; 
}

int Node::getWeight() { 
	return accumulatedWeight + heuristicWeight; 
}

bool Node::isVisited() { 
	return visit; 
}

bool Node::getWall() { 
	return isWall; 
}

int Node::getDistance(Hex other) { 
	return hexa.getHeuristicDistance(other); 
}

vector<Point2D> Node::getNeighbors(Point2D p) { 
	return Hex::getAdjacent(p);
}