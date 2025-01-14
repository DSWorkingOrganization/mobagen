#ifndef MOBAGEN_VORONOI_PEAKS_H
#define MOBAGEN_VORONOI_PEAKS_H

# include <cstdint>
# include <algorithm>
# include <array>
# include <iterator>
# include <numeric>
# include <random>
# include <type_traits>
#include <ColorT.h>

class VoronoiPeaks {
 public:
  explicit VoronoiPeaks(int64_t seed, int64_t peaks, std::vector<Color32> c, int side, double minValue, double maxValue);
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


};

#endif  // MOBAGEN_VORONOI_PEAKS_H