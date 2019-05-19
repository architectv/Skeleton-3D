#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <cmath>
#include <cstdint>
#include <stdexcept>

static_assert(sizeof (double) == 8, "double must be 8 bytes");
static_assert(sizeof (float) == 4, "float must be 4 bytes");

template <typename T>
struct TypeTraits;

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

template <typename FloatingPoint>
constexpr std::enable_if_t<std::is_floating_point<FloatingPoint>::value, bool> FuzzyCompare(FloatingPoint v1, FloatingPoint v2) {
  return Fabs(v1 - v2) * TypeTraits<FloatingPoint>::exp <= Min(Fabs(v1), Fabs(v2));
}

template <typename FloatingPoint>
constexpr std::enable_if_t<std::is_floating_point<FloatingPoint>::value, bool> FuzzyIsNull(FloatingPoint value) {
  return Fabs(value) <= TypeTraits<FloatingPoint>::eps;
}

// std::numeric_limits<T>::epsilon()
template <typename T>
struct TypeTraits {
  constexpr const static T eps = T{};

  constexpr static bool equals(const T& a, const T& b) { return a == b; }
};

template <>
struct TypeTraits<float> {
  constexpr const static float eps = 1e-5f;
  constexpr const static float exp = 1e5f;

  using null_t = std::uint32_t;
  constexpr const static null_t null = 0x7fffffff;

  constexpr static bool equals(float a, float b) { return FuzzyCompare(a, b); }
};

template <>
struct TypeTraits<double> {
  constexpr const static double eps = 1e-12;
  constexpr const static double exp = 1e12;

  using null_t = std::uint64_t;
  constexpr const static null_t null = 0x7fffffffffffffff;

  constexpr static bool equals(double a, double b) { return FuzzyCompare(a, b); }
};

template <typename FloatingPoint>
constexpr std::enable_if_t<std::is_floating_point<FloatingPoint>::value, bool> IsNull(FloatingPoint value) {
  union { FloatingPoint f; typename TypeTraits<FloatingPoint>::null_t u; } val = {value};
  return (val.u & static_cast<typename TypeTraits<FloatingPoint>::null_t>(TypeTraits<FloatingPoint>::null)) == 0;
}

template <typename T>
constexpr T Sqr(T t) {
  return t * t;
}

template <typename FloatingPoint>
constexpr std::enable_if_t<std::is_floating_point<FloatingPoint>::value, FloatingPoint> ToRadians(FloatingPoint angle) {
  return angle * M_PIl / 180.0;
}

template <typename FloatingPoint>
constexpr std::enable_if_t<std::is_floating_point<FloatingPoint>::value, FloatingPoint> ToDegrees(FloatingPoint angle) {
  return angle * 180.0 / M_PIl;
}

#endif // GLOBAL_H_
