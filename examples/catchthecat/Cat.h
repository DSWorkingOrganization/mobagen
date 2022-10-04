#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <concurrent_priority_queue.h>

using namespace std;

class Cat: public Agent {
  vector<unordered_set<bool, int>> frontier;

  // map of point 2 from
  // map of bool visted


 public:
    explicit Cat():Agent(){};
    Point2D Move(World *) override;
    Point2D findBestExit(World*);
    void getWorldNodes(World*);
};

#endif  // CAT_H
