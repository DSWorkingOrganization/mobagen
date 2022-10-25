#include "Agent.h"
#include "node.h"
#include "World.h"
#include <iostream>

using namespace std;

Point2D Agent::aStarSearch(World* world, map<int, map<int, Node>> weigh) 
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

          //abs(current.x) == halfWorldSide || abs(current.y) == halfWorldSide

		  if (abs(current.x) == halfWorldSide || abs(current.y) == halfWorldSide)       
          {
              exit = current;
              return exit;
              //break;
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

		  from[pod.getPos().y][pod.getPos().x] = current;
          visted[current.y][current.x] = true;

          lengthFrom++;
    }

}

Point2D Agent::escapPos(World* word, map<int, map<int, Node>> weigh) {
  auto cat = word->getCat();
    
  auto neighbors = Node::getNeighbors({cat.x, cat.y});

  vector<Node> randRet;

  for (int i = 0; i < neighbors.size(); i++) {
    if (validatePoint(neighbors[i], Point2D(0, 0), weigh)) {
      randRet.push_back(neighbors[i]);
    }
  }

  auto ran = Random::Range(0, randRet.size() - 1);

  return neighbors[ran];
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

  for (int line = -halfWorldSide; line <= halfWorldSide; line++) {
    for (int col = -halfWorldSide; col <= halfWorldSide; col++) {
      if ((abs(line) == halfWorldSide || abs(col) == halfWorldSide) &&
          (weigh[line][col].getWall() == false && weigh[line][col].getPos() != world->getCat()))
        nodes.push_back(weigh[line][col]);
    }
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
  int rand1;
  int rand2;

  do {
    rand1 = Random::Range(-size, size);
    rand2 = Random::Range(-size, size);
  } while (weigh[rand2][rand1].getWall() == true ||
           weigh[rand2][rand1].getPos() == world->getCat());
  
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
