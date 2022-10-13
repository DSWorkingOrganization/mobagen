#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <queue>
#include <map>
#include "node.h"
#include "compar.h"

using namespace std;

class World;

class Agent {
public:
  explicit Agent()= default;;
  virtual Point2D Move(World*)=0;

  map<int, map<int, Point2D>> from;
  map<int, map<int, bool>> visted;

  void aStarSearch(World* word, map<int, map<int, Node>> weigh);
  map<int, map<int, Node>> worldMap(World* world);
  Node getExitPos(World* world, map<int, map<int, Node>> weigh);
  Node panicBehavior(World* world, map<int, map<int, Node>> weigh);
  bool validatePoint(Point2D p, Point2D curre, map<int, map<int, Node>> worl);
  int findHeuristicFromCat(Node nood, World* world);
  int getWeightAround(Point2D find, map<int, map<int, Node>> nodes, int cBW);
  Point2D getPosInFind(int fromOr, World* worl, map<int, map<int, Point2D>> nodes);
  int getLength(int fromOr, World* worl, map<int, map<int, Node>> nodes);
  
  // map of bools, this is visited

  int currentWeight;
  int lengthFrom;

  priority_queue<Node, vector<Node>, sortPQNH> p;
};

#endif  // AGENT_H
