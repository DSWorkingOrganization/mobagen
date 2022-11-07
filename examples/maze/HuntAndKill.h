#ifndef HUNT_AND_KILL_H
#define HUNT_AND_KILL_H

#include "MazeGeneratorBase.h"
#include "Point2D.h"
#include "Node.h"
#include <map>
#include <vector>

using namespace std;
class World;

// please do not use this one anymore. Move your code to the specific
// implementation. I am going to rename this interface soon to be a naive
// implementation.
class HuntAndKill : public MazeGeneratorBase {
 public:
  HuntAndKill() = default;
  std::string GetName() override { return "Hunt and Kill"; };
  // todo: in order to step work properly, you have to store your current
  // exploration status in the MazeGenerator members Steps should return true if
  // it made changes in the world
  bool Step(World* world);
  // Clears and resets all data from the generator
  void Clear(World* world);
  // todo: in order to step work properly, you have to store your current
  // exploration status in the MazeGenerator members

  private:
  vector<Point2D> getAdjac(World* w, const Point2D& p);

  Point2D parseRow(World* world, int y);

  Point2D walk(World* world, Point2D pos);

  Point2D hunt(World* world);

  void clearBack(World* world, Point2D pos, Point2D from);

  Point2D internalPos;

  bool hasStarted;

  bool cantHunt;

  bool startHunting;

  bool bud;

  int siz;

  int sizOv2;

  Point2D stack;

  vector<bool> visited;
};

#endif
