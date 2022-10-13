#ifndef CATCHER_H
#define CATCHER_H

#include "Agent.h"

class Catcher: public Agent {
 public:
    explicit Catcher():Agent(){};
    Point2D Move(World*) override;

    int calcDist(World* worl);
    int getNum;
};

#endif  // CATCHER_H
