#ifndef COMPAR_H
#define COMPAR_H
#include "Point2D.h"
#include "node.h"

struct sortPQN 
{
  bool operator()(Node& a, Node& b);
};

struct sortPQNH 
{
  bool operator()(Node& a, Node& b);
};

#endif  // COMPAR_H