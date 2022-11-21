#ifndef MOBAGEN_MYGENERATOR_H
#define MOBAGEN_MYGENERATOR_H

#include "../GeneratorBase.h"
#include "../TwinSystem.h"
#include "../VoronoiPeaks.h"
#include "../FastNoiseLite.h"
#include <iostream>

class MyGenerator : public ScenarioGeneratorBase {
 public:
  std::vector<Color32> Generate(int sideSize, float displacement) override;
  std::string GetName() override;
};

#endif  // MOBAGEN_MYGENERATOR_H