#include "node.h"
#include "World.h"
#include <stdexcept>

using namespace std;

Node::Node() 
{ 
	poin = new Point2D(0, 0); 
	hexa = {poin->x, poin->y};
}

Node::Node(Point2D* pos) 
{ 
	poin = pos; 
	hexa = {poin->x, poin->y};
}

Node::~Node() {
  delete poin;
  poin = nullptr;
}

void Node::setPoint(Point2D* pos) { 
	poin = pos; 
}

void Node::setAWeight(int weight) { 
	accumulatedWeight = weight; 
}

void Node::setHWeight(Point2D destination) {
  int dx = abs(poin->x - destination.x);
  int dy = abs(poin->y - destination.y);

}

void Node::setVisted(bool visited) { 
	visit = visited;
}

void Node::setWall(bool wall) { 
	isWall = wall; 
}

Point2D Node::getPos() { 
	return *poin; 
}

int Node::getWeight() { 
	return accumulatedWeight + heuristicWeight; 
}

bool Node::isVisited() { 
	return visit; 
}