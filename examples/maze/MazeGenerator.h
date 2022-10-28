#ifndef MOBAGEN_MAZEGENERATOR_H
#define MOBAGEN_MAZEGENERATOR_H

#include "Point2D.h"
#include <map>

using namespace std;

class World;

class MazeGenerator {
 public:
  // todo: in order to step work properly, you have to store your current
  // exploration status in the MazeGenerator members
  
  map<int, map<int, Point2D>> layOut;
  map<int, map<int, Point2D>> worldMap(World* world);
  void Step(World * world);
};

#endif
