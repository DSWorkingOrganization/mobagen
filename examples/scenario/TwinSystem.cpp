#include "TwinSystem.h"

TwinSystem::TwinSystem(int64_t seed, int64_t peaks, std::vector<Color32> c,
                       int side, float depth, float width, float rain,
                       float flow, float pick, float drop, float solu,
                       float vapor, double minValue = -1, double maxValue = 1) {
  rainfall = rain;
  rainflow = flow;
  pickThreshold = pick;
  dropThreshold = drop;
  solubility = solu;
  evaporation = vapor;

  for (int i = 0; i < side; i++) 
  {
    for (int j = 0; j < side; j++) 
    {
      finalElevation[i][j] = 0;
      elevation[i][j] = 0;
      water[i][j] = 0;
      material[i][j] = 0;
      previousMaterial[i][j] = 0;
      waterFlow[i][j] = Dir4();
      totalFlow[i][j] = 0;
      waterVelocity[i][j] = {0, 0};
    }
  }


}

void TwinSystem::rain(int x, int y) 
{ 
    water[x][y] += rainfall; 
}

void TwinSystem::calculateFlow(int x, int y) {
  totalFlow[x][y] = 0;

  for (int i = 0; i < 4; i++) {
    dh = elevation[x][y] - elevation[x + DIRNS[i].x][y + DIRNS[i].y];
    dw = water[x][y] - water[x + DIRNS[i].x][y + DIRNS[i].y];
    waterFlow[x][y].dir[i] += rainflow * (dh + dw);
    if (waterFlow[x][y].dir[i] < 0) waterFlow[x][y].dir[i] = 0;
    totalFlow[x][y] += waterFlow[x][y].dir[i];
  }

  if (totalFlow[x][y] > water[x][y]) 
  {
    prop = water[x][y] / totalFlow[x][y];
    for (int i = 0; i < 4; i++) 
        waterFlow[x][y].dir[i] *= prop;
  }

  hOut = waterFlow[x][y].dir[0] - waterFlow[x][y].dir[3];
  hIn = waterFlow[x + 1][y].dir[3] - waterFlow[x - 1][y].dir[0];
  vOut = waterFlow[x][y].dir[1] - waterFlow[x][y].dir[2];
  vIn = waterFlow[x][y + 1].dir[2] - waterFlow[x][y - 1].dir[1];
  waterVelocity[x][y] = Vector2(hOut + hIn, vOut + vIn);
}

void TwinSystem::erodeDeposit(int x, int y) 
{
  waterSpeed = waterVelocity[x][y].getMagnitude();

  if (waterSpeed > pickThreshold) 
  {
    pck = waterSpeed * solubility;
    material[x][y] += pck;
    elevation[x][y] -= pck;
  } 
  else if (waterSpeed < dropThreshold) 
  {
    prop = (dropThreshold - waterSpeed) / dropThreshold;
    drp = prop * material[x][y];
    material[x][y] -= drp;
    elevation[x][y] += drp;
  }
}

void TwinSystem::flow(int x, int y) 
{
  for (int i = 0; i < 4; i++) {
    waterFlowing = waterFlow[x][y].dir[i];
    prop = waterFlowing / totalFlow[x][y];
    materialSrc = material[x][y];
    materialFlowing = prop * materialSrc;

    water[x][y] -= waterFlowing;
    water[x + DIRNS[i].x][y + DIRNS[i].y] += waterFlowing;
    material[x][y] -= materialFlowing;
    material[x + DIRNS[i].x][y + DIRNS[i].y] += materialFlowing;
  }
}

void TwinSystem::evaporate(int x, int y) 
{ water[x][y] *= (1 - evaporation); }

float TwinSystem::getNoise(int x, int y) { return finalElevation[x][y]; }