#include "Cat.h"
#include "World.h"
#include <stdexcept>

using namespace std;

Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0,5);
  auto pos = world->getCat();
  switch(rand){
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}

//Point2D Cat::

void Cat::getWorldNodes(World* world) {
    frontier.clear();

    for (int i = 0; i < world->getWorldSideSize(); i++) {
      //frontier.push_back(unordered_set); 
    }
}