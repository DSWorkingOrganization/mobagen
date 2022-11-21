#include "MyGenerator.h"

using namespace std;

vector<Color32> MyGenerator::Generate(int sideSize, float displacement = 0) {
  vector<float> colorState;
  vector<Color32> colors;
  FastNoiseLite base;
  base.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
  int colorBase;

  for (int l = 0; l < sideSize; l++)
    for (int c = 0; c < sideSize; c++)
      colorState.emplace_back(base.GetNoise((float)c, (float)l, displacement * 50));

  TwinSystem sys(colorState, sideSize, .9, 1, .9, -.4, .5, -.5, .3, .7, -1, 1);

  for (int l = 0; l < sideSize; l++) 
  {
    for (int c = 0; c < sideSize; c++) 
    {
      colorBase = ((sys.getNoise(c, l) +1.0)/2.0) * 255.0;
      colors.emplace_back(colorBase, colorBase, colorBase);
    }
  }
  
  std::cout << colors.size() << std::endl;
  return colors;
}

string MyGenerator::GetName() { return "CRACKED EROSION"; }