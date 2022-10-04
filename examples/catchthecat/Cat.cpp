#include "Cat.h"
#include "World.h"
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

Point2D Cat::Move(World* world) {

  auto cat = world->getCat();
  //visited cat y cat x true
  // if visted find keyval 0 != visited.end and visted[0]

  //vector<queue, q push back

  // While queue isn't empty, head = q 0
  // que erase begin
  // mark head as visted

  // for each neighbor check if is not in q, unvisted, can be visted, and add to q, adding 1 to its weight
  // Mark the neighbor as it came from the current head



  // here I code in the win condition and navigation

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