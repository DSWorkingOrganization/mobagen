#include "compar.h"
#include "node.h"

bool sortPQN::operator()(Node& a, Node& b) {
  return a.getHWeight() > b.getHWeight();
}

bool sortPQNH::operator()(Node& a, Node& b) {
  return a.getWeight() > b.getWeight();
}