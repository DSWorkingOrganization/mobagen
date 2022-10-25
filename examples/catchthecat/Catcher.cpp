#include "Catcher.h"
#include "World.h"
#include <cstdlib>

using namespace std;

Point2D Catcher::Move(World* world) {
  auto cat = world->getCat();
    
    /*
  auto side = world->getWorldSideSize()/2;
  for(;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if(cat.x!=p.x && cat.y!=p.y && !world->getContent(p))
      return p;
  }
  */

  auto exit = aStarSearch(world, worldMap(world));

  vector<Point2D> path;

  if (exit.x != INT_MAX) {
    for (auto e = exit; e != cat; e = from[e.y][e.x]) {
      path.push_back(e);
    }
  }

  int p = Random::Range(0, path.size() - 1);

  return path[0];



  /*
  auto finNum = calcDist(world);

  if (lengthFrom > 2)
    finNum = Random::Range(1, lengthFrom - 1);
  else
    finNum = 1;

  for (int i = 0; i < getNum; i++) {
    p.pop();
  }

  auto finPlace = getPosInFind(finNum, world, from);

  return finPlace;
  */
}

int Catcher::calcDist(World* worl) {
  int halfWorldSide = worl->getWorldSideSize() / 2;

  if (halfWorldSide < p.size() && p.size() > 2) return p.size() / 2;
  if (halfWorldSide / 2 > p.size() && p.size() > 2) return 3 * p.size() / 4;
  if (halfWorldSide / 4 > p.size() && p.size() > 2) return p.size() - 1;
  if (halfWorldSide > p.size()) return 1;
}
