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

  void setQ(int q);
  void setR(int r);
  void setS(int s);

  hexCoord getCoord();
  int getHeuristicDistance(Hex other);
  static vector<Point2D> getAdjacent(Point2D p);

 private:
  hexCoord cord;
};

#endif // HEX_H