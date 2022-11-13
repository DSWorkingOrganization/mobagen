#include "HuntAndKill.h"
#include "World.h"
#include "Node.h"
#include "MazeGenerator.h"
#include "GameObject.h"

bool HuntAndKill::Step(World* world) 
{ 
	if (hasStarted == false) {
        siz = world->GetSize();
        siz *= siz;
        sizOv2 = world->GetSize() / 2;
        internalPos = {rand() % world->GetSize() - sizOv2, rand() % world->GetSize() - sizOv2};
    }   

   if (startHunting == false) 
   {
       internalPos = walk(world, internalPos);
   }
   else 
   {
       internalPos = hunt(world);
     if (cantHunt == false) internalPos = walk(world, internalPos);
   }

   if (hasStarted == false) hasStarted = true;

   if (startHunting && cantHunt)
     return false;
   else
     return true;
}

void HuntAndKill::Clear(World* world) 
{ 
    internalPos = {NULL, NULL};
    stack = {NULL, NULL};
    siz = 0;
    sizOv2 = 0;
    hasStarted = false;
    startHunting = false;
    cantHunt = false;
    bud = false;

    visitor.clear();
}

vector<Point2D> HuntAndKill::getAdjac(World* w, const Point2D& p) 
{
  vector<Point2D> visitables;

  // north
  if (abs(p.x) <= sizOv2 &&
      abs(p.y - 1) <= sizOv2 &&  // should be inside the board
      !visitor[p.y - 1][p.x])
    visitables.emplace_back(p.x, p.y - 1);
  // east
  if (abs(p.x + 1) <= sizOv2 &&
      abs(p.y) <= sizOv2 &&  // should be inside the board
      !visitor[p.y][p.x + 1])
    visitables.emplace_back(p.x + 1, p.y);
  // south
  if (abs(p.x) <= sizOv2 &&
      abs(p.y + 1) <= sizOv2 &&  // should be inside the board
      !visitor[p.y + 1][p.x])
    visitables.emplace_back(p.x, p.y + 1);
  // west
  if (abs(p.x - 1) <= sizOv2 &&
      abs(p.y) <= sizOv2 &&  // should be inside the board
      !visitor[p.y][p.x - 1])
    visitables.emplace_back(p.x - 1, p.y);

  return visitables;
}

Point2D HuntAndKill::parseRow(World* world, int y)
{
  bool found;
  Point2D parseData;

  for (int j = -(sizOv2); j < (sizOv2) + 1; j++) {
    if ((abs(j) <= sizOv2 && abs(y - 1) <= sizOv2) && visitor[y - 1][j] &&
        !visitor[y][j])
      {
          world->SetNorth({j, y}, false);
          world->SetEast({j, y}, true);
          world->SetSouth({j, y}, true);
          world->SetWest({j, y}, true);
          return {j, y};
    } else if ((abs(j + 1) <= sizOv2 && abs(y) <= sizOv2) && visitor[y][j + 1] &&
               !visitor[y][j])
      {
        world->SetNorth({j, y}, true);
        world->SetEast({j, y}, false);
        world->SetSouth({j, y}, true); 
        world->SetWest({j, y}, true);
          return {j, y};
    } else if ((abs(j) <= sizOv2 && abs(y + 1) <= sizOv2) && visitor[y + 1][j] &&
               !visitor[y][j]) 
      {
        world->SetNorth({j, y}, true);
        world->SetEast({j, y}, true);
        world->SetSouth({j, y}, false);
        world->SetWest({j, y}, true);
          return {j, y};
    } else if ((abs(j - 1) <= sizOv2 && abs(y) <= sizOv2) && visitor[y][j-1] &&
               !visitor[y][j]) 
      {
        world->SetNorth({j, y}, true);
        world->SetEast({j, y}, true);
        world->SetSouth({j, y}, true);
        world->SetWest({j, y}, false);
          return {j, y};
      }
  }

  return {sizOv2 + 1, NULL};
}

Point2D HuntAndKill::walk(World* world, Point2D pos) 
{
  startHunting = false;
  
  Point2D returnPoint = pos;

  visitor[returnPoint.y][returnPoint.x] = true;

  if (bud == false) {
    world->SetNodeColor(returnPoint, Color::Black);

    world->SetNode(returnPoint, {true, true, true, true});

    if (hasStarted == true) clearBack(world, returnPoint, stack);
  } else
    bud = false;

  vector<Point2D> neighbors = getAdjac(world, returnPoint);

  if (neighbors.size() != 0) {
    Point2D pon = neighbors[rand() % neighbors.size()];
    stack = returnPoint;
    return pon;
  } 
  else 
  {
    startHunting = true;

    return returnPoint;
  }
}

Point2D HuntAndKill::hunt(World* world) {
    Point2D pont;
    for (int i = -sizOv2; i <= sizOv2 ; i++)
    {
        pont = parseRow(world, i);
        if (pont.x <= sizOv2) 
        {
            world->SetNodeColor(pont, Color::Black);
            startHunting = false;
            bud = true;
            return pont;
        }
    }

    cantHunt = true;
    return {sizOv2 + 1, NULL};
}

void HuntAndKill::clearBack(World* world, Point2D pos, Point2D from) 
{ 
    if (pos.x < from.x) world->SetEast(pos, false);
    if (pos.x > from.x) world->SetWest(pos, false);
    if (pos.y > from.y) world->SetNorth(pos, false);
    if (pos.y < from.y) world->SetSouth(pos, false);
}