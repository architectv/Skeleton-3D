#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cmath>
#include <cstdint>
#include <stdexcept>

static_assert(sizeof (double) == 8, "double must be 8 bytes");
static_assert(sizeof (float) == 4, "float must be 4 bytes");

template <typename FloatingPoint>
constexpr std::enable_if_t<std::is_floating_point<FloatingPoint>::value, bool> Fabs(FloatingPoint x) {
  return x >= 0 ? x : -x;
}

template <typename T, typename U>
constexpr auto Min(const T& a, const U& b) -> std::common_type_t<const T&, const U&> {
  return a < b ? a : b;
}

template <typename T, typename U, typename... Args>
constexpr auto Min(const T& a, const U& b, const Args&... args) -> std::common_type_t<const T&, const U&, const Args&...> {
  return Min(Min(a, b), args...);
}

template <typename T, typename U>
constexpr auto Max(const T& a, const U& b) -> std::common_type_t<const T&, const U&> {
  return a > b ? a : b;
}

template <typename T, typename U, typename... Args>
constexpr auto Max(const T& a, const U& b, const Args&... args) -> std::common_type_t<const T&, const U&, const Args&...> {
  return Max(Max(a, b), args...);
}

constexpr bool FuzzyCompare(double d1, double d2) {
  return Fabs(d1 - d2) * 1e12 <= Min(Fabs(d1), Fabs(d2));
}

constexpr bool FuzzyCompare(float f1, float f2) {
  return Fabs(f1 - f2) * 1e5f <= Min(Fabs(f1), Fabs(f2));
}

constexpr bool FuzzyIsNull(double d) {
  return Fabs(d) <= 1e-12;
}

constexpr bool FuzzyIsNull(float f) {
  return Fabs(f) <= 1e-5f;
}

constexpr bool IsNull(double d) {
  union U { double d; std::uint64_t u; } val = {d};
  return (val.u & static_cast<std::uint64_t>(0x7fffffffffffffff)) == 0;
}

constexpr bool IsNull(float f) {
  union U { float f; std::uint32_t u; } val = {f};
  return (val.u & 0x7fffffff) == 0;
}

template <typename T>
constexpr T Sqr(T t) {
  return t * t;
}

template <typename FloatingPoint>
constexpr std::enable_if_t<std::is_floating_point<FloatingPoint>::value, FloatingPoint> ToRadians(FloatingPoint angle) {
  return angle * M_PI / 180.0f;
}

template <typename FloatingPoint>
constexpr std::enable_if_t<std::is_floating_point<FloatingPoint>::value, FloatingPoint> ToDegrees(FloatingPoint angle) {
  return angle * 180.f / M_PI;
}

#endif // GLOBAL_H_