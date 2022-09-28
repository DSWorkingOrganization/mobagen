#include "hexCoord.h"

using namespace std;

hexCoord::hexCoord() { 
	// Point2D NE(1, -1), Point2D NW(0, -1), Point2D E(1, 0), Point2D W(-1, 0), Point2D SE(1, 1), Point2D(0, 1)
	if (neighborDifferences == nullptr) {
		neighborDifferences[0] = Point2D (1, -1);
        neighborDifferences[1] = Point2D (0, -1);
        neighborDifferences[2] = Point2D (1, 0);
        neighborDifferences[3] = Point2D (-1, 0);
        neighborDifferences[4] = Point2D (1, 1);
        neighborDifferences[5] = Point2D (0, 1);
	}
}

hexCoord::hexCoord(int makeQ, int makeR) {
  q = makeQ;
  r = makeR;
}

hexCoord::hexCoord(int makeQ, int makeR, int makeS) {
  q = makeQ;
  r = makeR;
  s = makeS;
}

hexCoord::~hexCoord() {

}

void hexCoord::setQ(int makeQ) { 
	q = makeQ;
}

void hexCoord::setR(int makeR) { 
	r = makeR;
}

void hexCoord::setS(int makeS) { 
	s = makeS; 
}

int hexCoord::getQ() { 
	return q;
}

int hexCoord::getR() { 
	return r;
}

int hexCoord::getS() { 
	return s;
}

hexCoord hexCoord::axialToDoubled(hexCoord coord) {
  q = coord.getQ() + (coord.getR() - (coord.getR() & 1)) / 2;
  r = coord.getR();

  return hexCoord(q, r);
}

hexCoord hexCoord::doubledToAxial(hexCoord coord) {
  q = coord.getQ() - (coord.getR() - (coord.getR() & 1)) / 2;
  r = coord.getR();

  return hexCoord(q, r);
}

Point2D hexCoord::getOffsetCoord() { 
	return Point2D(q, r);
}

int hexCoord::axialDistance(hexCoord axiA, hexCoord axiB) {
  return (abs(axiA.getQ() - axiB.getQ()) +
             abs(axiA.getQ() + axiA.getR() - axiA.getQ() - axiB.getR()),
                  abs(axiA.getR() - axiB.getR())) / 2;
}

int hexCoord::offsetDistance(hexCoord A, hexCoord B) {
  hexCoord aC = doubledToAxial(A);
  hexCoord bC = doubledToAxial(B);

  return axialDistance(aC, bC);
}