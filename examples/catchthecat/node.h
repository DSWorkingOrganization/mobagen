#ifndef NODE_H
#define NODE_H

#include <Point2D.h>
#include <math.h>

using namespace std;

class Node {
 public:
  Node();
  Node(Point2D* pos);
  ~Node();

  void setPoint(Point2D* pos);
  void setAWeight(int weight);
  void setHWeight(Point2D destination);
  void setVisted(bool visited);
  void setWall(bool wall);

  Point2D getPos();
  int getWeight();
  bool isVisited();

 private:
  Point2D* poin;
  int accumulatedWeight;
  int heuristicWeight;
  bool visit;
  bool isWall;
};

#endif  // NODE_H