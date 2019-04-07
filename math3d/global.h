#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cmath>
#include <cstdint>
#include <algorithm>

static_assert(sizeof (double) == 8, "double must be 8 bytes");
static_assert(sizeof (float) == 4, "float must be 4 bytes");

constexpr static inline bool FuzzyCompare(double d1, double d2) {
  return std::abs(d1 - d2) * 1e12 <= std::min(std::abs(d1), std::abs(d2));
}

constexpr static inline bool FuzzyCompare(float f1, float f2) {
  return std::abs(f1 - f2) * 1e5f <= std::min(std::abs(f1), std::abs(f2));
}

constexpr static inline bool FuzzyIsNull(double d) {
  return std::abs(d) <= 1e-12;
}

constexpr static inline bool FuzzyIsNull(float f) {
  return std::abs(f) <= 1e-5f;
}

constexpr static inline bool IsNull(double d) {
  union U { double d; std::uint64_t u; } val = {d};
  return (val.u & static_cast<std::uint64_t>(0x7fffffffffffffff)) == 0;
}

constexpr static inline bool IsNull(float f) {
  union U { float f; std::uint32_t u; } val = {f};
  return (val.u & 0x7fffffff) == 0;
}

template <typename T>
constexpr static inline T Sqr(T t) {
  return t * t;
}

#endif  // GLOBAL_H_
