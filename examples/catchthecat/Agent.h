#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"

#include <map>

using namespace std;

class World;

class Agent {
public:
  explicit Agent()= default;;
  virtual Point2D Move(World*)=0;

  map<int, map<int, Point2D>> from;
  map<int, map<int, bool>> visted;

  void aStarSearch(World* word);
  // map of bools, this is visited
};

#endif  // AGENT_H
