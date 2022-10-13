#ifndef HEXCOORD_H
#define HEXCOORD_H

#include <Point2D.h>
#include <math.h>

class hexCoord {
 public:
  hexCoord();
  hexCoord(int makeQ, int makeR);
  hexCoord(int makeQ, int makeR, int makeS);
  ~hexCoord();

  void setQ(int makeQ);
  void setR(int makeR);
  void setS(int makeS);

  int getQ();
  int getR();
  int getS();

  hexCoord axialToDoubled(hexCoord coord);
  hexCoord doubledToAxial(hexCoord coord);

  Point2D getOffsetCoord();

  int axialDistance(hexCoord axiA, hexCoord axiB);
  int offsetDistance(hexCoord A, hexCoord B);

  Point2D neighborDifferences[6];

 private:
  int q;
  int r;
  int s;
};

#endif // HEXCOORD_H`
