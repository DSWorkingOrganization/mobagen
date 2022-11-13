#ifndef MOBAGEN_VORONOI_PEAKS_H
#define MOBAGEN_VORONOI_PEAKS_H

# include <cstdint>
# include <algorithm>
# include <array>
# include <iterator>
# include <numeric>
# include <random>
# include <type_traits>
#include <Manager.h>

class VoronoiPeaks {
 public:
  explicit generatePeaks(Manager man, int64_t seed, int64_t peaks);
};

#endif  // MOBAGEN_VORONOI_PEAKS_H