#ifndef HEX_H
#define HEX_H

#include "hexCoord.h"
#include <Point2D.h>
#include <vector>

using namespace std;

class Hex {
 public:
  Hex();
  Hex(int q, int r);
  Hex(int q, int r, int s);
  ~Hex();

  hexCoord getCoord();
  int getHeuristicDistance(Hex other);
  vector<Point2D> getAdjacent(int mapsize);

 private:
  hexCoord cord;
};

#endif // HEX_H