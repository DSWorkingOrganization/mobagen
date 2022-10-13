#ifndef NODE_H
#define NODE_H

#include <Point2D.h>
#include <math.h>
#include "hex.h"

using namespace std;

class Node {
 public:
  Node();
  Node(Point2D pos);
  ~Node();

  void setPoint(Point2D pos);
  void setAWeight(int weight);
  void setHWeight(Point2D destination, int worldSize);
  void setVisted(bool visited);
  void setWall(bool wall);
  int getAWeight() { 
      return accumulatedWeight;
  }
  int getHWeight() { 
      return heuristicWeight;
  }
  bool operator<(const Node& rhs) const {
    return accumulatedWeight < rhs.accumulatedWeight;
  }
  static vector<Point2D> getNeighbors(Point2D p);

  Point2D getPos();
  int getWeight();
  bool isVisited();
  bool getWall();
  int getDistance(Hex other);

 private:
  Point2D poin;
  Point2D from;
  Hex hexa;
  int accumulatedWeight;
  int heuristicWeight;
  bool visit;
  bool isWall;
};

#endif  // NODE_H