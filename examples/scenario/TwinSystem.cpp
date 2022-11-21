#include "TwinSystem.h"

TwinSystem::TwinSystem(std::vector<float> c,
                       int side, float depth, float width, float rain,
                       float flow, float pick, float drop, float solu,
                       float vapor, double minValue = -1, double maxValue = 1) {
  rainfall = rain;
  if (rainfall > maxValue)
    rainfall = maxValue;
  else if (rainfall < minValue)
    rainfall = minValue;

  rainflow = flow;
  if (rainflow > maxValue)
    rainflow = maxValue;
  else if (rainflow < minValue)
    rainflow = minValue;

  pickThreshold = pick;
  if (pickThreshold > maxValue)
    pickThreshold = maxValue;
  else if (pickThreshold < minValue)
    pickThreshold = minValue;

  dropThreshold = drop;
  if (dropThreshold > maxValue)
    dropThreshold = maxValue;
  else if (dropThreshold < minValue)
    dropThreshold = minValue;

  solubility = solu;
  if (solubility > maxValue)
    solubility = maxValue;
  else if (solubility < minValue)
    solubility = minValue;

  evaporation = vapor;
  if (evaporation > maxValue)
    evaporation = maxValue;
  else if (evaporation < minValue)
    evaporation = minValue;


  for (int i = 0; i < side; i++) {
    for (int j = 0; j < side; j++) {
      finalElevation[i][j] = 0;
      elevation[i][j] = c[(side * i) + j];
      water[i][j] = 0;
      material[i][j] = 0;
      previousMaterial[i][j] = 0;
      waterFlow[i][j] = Dir4();
      totalFlow[i][j] = 0;
      waterVelocity[i][j] = {0, 0};
    }
  }

  
  cx = rand() % side;
  cy = rand() % side;

  direc = (rand() / (float)RAND_MAX) * 2.0f * M_PI;

  dx = cosf(direc);
  dy = sinf(direc);

  for (int x = 0; x < side; x++) {
    for (int y = 0; y < side; y++) {
      ox, oy = cx - x, cy - y;
      dp = ox * dx + oy * dy;

      if (dp > 0)
        change = depth * width / (width + dp);
      else
        change = -depth * width / (width - dp);

      elevation[x][y] += change;
    }
  }
  

  
  for (int x = 0; x < side; x++) {
    for (int y = 0; y < side; y++) {
      raining(x, y);
      calculateFlow(x, y);
      erodeDeposit(x, y);
      flowing(x, y);
      evaporate(x, y);
      
      if (elevation[x][y] > maxValue)
        elevation[x][y] = maxValue;
      else if (elevation[x][y] < minValue)
        elevation[x][y] = minValue;
        
    }
  }
  

  for (int i = 0; i < side; i++)
    for (int j = 0; j < side; j++) 
        finalElevation[i][j] = elevation[i][j];
}

void TwinSystem::raining(int x, int y) 
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

void TwinSystem::flowing(int x, int y) 
{
  materialSrc = material[x][y];
  for (int i = 0; i < 4; i++) {
    waterFlowing = waterFlow[x][y].dir[i];
    prop = waterFlowing / totalFlow[x][y];
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