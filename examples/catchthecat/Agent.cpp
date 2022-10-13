#include "Agent.h"
#include "node.h"
#include "World.h"
#include <iostream>

using namespace std;

void Agent::aStarSearch(World* world, map<int, map<int, Node>> weigh) 
{
    int halfWorldSide = world->getWorldSideSize() / 2;
	currentWeight = 0;
    lengthFrom = 0;
	from.clear();
    visted.clear();

	priority_queue<Node, vector<Node>, sortPQN> q;
	Node head = Node(world->getCat());
    head.setAWeight(currentWeight);
    p.push(head);

	Point2D current;

	Point2D goal = getExitPos(world, weigh).getPos();

    Point2D exit(INT_MAX, INT_MAX);

	while (p.empty() == false) 
	{
          Node pod = p.top();
          p.pop();
		  current = pod.getPos();

          while (p.empty() == false) {
            p.pop();
          }

		  if (abs(current.x) == halfWorldSide || abs(current.y) == halfWorldSide)       
          {
              exit = current;
              break;
          }

		  auto neighbors = Node::getNeighbors({current.x, current.y});

		  for (int i = 0; i < neighbors.size(); i++) 
		  {
			  if (validatePoint(neighbors[i], current, weigh)) {
                 Node no(neighbors[i]);
                 no.setAWeight(pod.getAWeight() + 1);
                 no.setHWeight(goal, halfWorldSide);
                 p.push(no);
			  }
		  }

          pod = p.top();

		  from[current.y][current.x] = pod.getPos();
          visted[current.y][current.x] = true;

          lengthFrom++;
    }

}

map<int, map<int, Node>> Agent::worldMap(World* world) {
  int halfWorldSide = world->getWorldSideSize() / 2;
  map<int, map<int, Node>> complexWorld;

  for (int line = -halfWorldSide; line <= halfWorldSide; line++) 
  {
    for (int col = -halfWorldSide; col <= halfWorldSide; col++) 
	{
      complexWorld[line][col] = Node(Point2D(col, line));
      complexWorld[line][col].setWall(world->getContent(col, line));
	}
  }

  //complexWorld

  return complexWorld;
}

Node Agent::getExitPos(World* world, map<int, map<int, Node>> weigh) {
  int halfWorldSide = world->getWorldSideSize() / 2;
  vector<Node> nodes;
  Node returner;

  //map<int, map<int, Node>> findMap = weigh;

  for (int i = -halfWorldSide; i <= halfWorldSide; i++) {
    if (weigh[i][-halfWorldSide].getWall() == false) {
      nodes.push_back(weigh[i][-halfWorldSide]);
	}
  }

  for (int j = -halfWorldSide; j <= halfWorldSide; j++) {
    if (weigh[j][halfWorldSide].getWall() == false) {
      nodes.push_back(weigh[j][halfWorldSide]);
    }
  }

  for (int k = -halfWorldSide; k < halfWorldSide; k++) {
    if (weigh[-halfWorldSide][k].getWall() == false)
      nodes.push_back(weigh[-halfWorldSide][k]);
    if (weigh[halfWorldSide][k].getWall() == false)
      nodes.push_back(weigh[halfWorldSide][k]);
  }

  if (nodes.empty() == false) {
    returner = nodes[0];
    for (int i = 1; i < nodes.size(); i++) {
      if (findHeuristicFromCat(returner, world) < findHeuristicFromCat(nodes[i], world)) {
        returner = nodes[i];
	  }
	}
  } else {
    returner = panicBehavior(world, weigh);
  }

  return returner;
}

Node Agent::panicBehavior(World* world, map<int, map<int, Node>> weigh) {
  int size = world->getWorldSideSize() / 2;
  auto rand1 = Random::Range(-size, size);
  auto rand2 = Random::Range(-size, size);
  
  return weigh[rand2][rand1];
}

bool Agent::validatePoint(Point2D p, Point2D curre, map<int, map<int, Node>> worl) {
  if (worl[p.y][p.x].getWall() == false && (visted[p.y][p.x] == false && p != from[curre.y][curre.x]))
    return true;
  else
    return false;
}

int Agent::findHeuristicFromCat(Node nood, World* world) {
  Hex cat(world->getCat().x, world->getCat().y);

  return nood.getDistance(cat);
}

int Agent::getWeightAround(Point2D find, map<int, map<int, Node>> nodes, int cBW) {
  return 0;
}

Point2D Agent::getPosInFind(int fromOr, World* worl, map<int, map<int, Point2D>> nodes) {
  int halfWorldSide = worl->getWorldSideSize() / 2;
    
  Point2D punts(worl->getCat());

  for (int i = 0; i < fromOr; i++) {
    for (int line = -halfWorldSide; line <= halfWorldSide; line++) {
      for (int col = -halfWorldSide; col <= halfWorldSide; col++) {
        if (line == punts.y && col == punts.x) {
          punts = nodes[line][col];
        }
      }
    }
  }

  return punts;
}
