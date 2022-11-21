#ifndef MOBAGEN_TWIN_SYSTEM_H
#define MOBAGEN_TWIN_SYSTEM_H

#include <ColorT.h>
#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <numeric>
#include <random>
#include <type_traits>
#include <Point2D.h>
#include <Vector2.h>
#include <map>
#include "Dir4.h"

using namespace std;

class TwinSystem {
 public:
  explicit TwinSystem(std::vector<float> c,
                      int side, float depth, float width, float rain,
                      float flow, float pick, float drop, float solu, float vapor,
                      double minValue, double maxValue);
  float getNoise(int x, int y);
 private:
  std::mt19937_64 generator;
  std::uniform_real_distribution<double> distribution;
  std::vector<double> samples;

  inline constexpr double Fade(const double t) noexcept {
    return t * t * t * (t * (t * 6 - 15) + 10);
  }

  inline constexpr double Lerp(const double a, const double b,
                               const double t) noexcept {
    return (a + (b - a) * t);
  }

  inline constexpr double Grad(const std::uint64_t hash, const double x,
                               const double y, const double z) noexcept {
    const std::uint8_t h = hash & 15;
    const double u = h < 8 ? x : y;
    const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
  }

  float rainfall;
  float rainflow;
  float pickThreshold;
  float dropThreshold;
  float evaporation;
  float solubility;
  const Point2D DIRNS[4] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
  float waterSpeed;
  float waterFlowing;
  float materialFlowing;
  float materialSrc;
  float dh, dw, prop, hOut, hIn, vOut, vIn, pck, drp, cx, cy, direc, dx, dy, ox,
      oy, dp, change;

  map<int, map<int, float>> finalElevation;

  map<int, map<int, float>> elevation;
  map<int, map<int, float>> water;
  map<int, map<int, float>> material;

  map<int, map<int, float>> previousMaterial;

  // The 3rd means 4
  map<int, map<int, Dir4>> waterFlow;
  map<int, map<int, float>> totalFlow;
  map<int, map<int, Vector2>> waterVelocity;

  void raining(int x, int y);
  void calculateFlow(int x, int y);
  void erodeDeposit(int x, int y);
  void flowing(int x, int y);
  void evaporate(int x, int y);
};

#endif  // MOBAGEN_TWIN_SYSTEM_H