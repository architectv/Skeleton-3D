template <typename T>
constexpr Vector4<T> Vector4<T>::x_axis(T value) {
  return {value, T{}, T{}, T{}};
}

template <typename T>
constexpr Vector4<T> Vector4<T>::y_axis(T value) {
  return {T{}, value, T{}, T{}};
}

template <typename T>
constexpr Vector4<T> Vector4<T>::z_axis(T value) {
  return {T{}, T{}, value, T{}};
}

template <typename T>
constexpr Vector4<T> Vector4<T>::w_axis(T value) {
  return {T{}, T{}, T{}, value};
}

template <typename T>
constexpr Vector4<T> Vector4<T>::x_scale(T value) {
  return {value, T(1), T(1), T(1)};
}

template <typename T>
constexpr Vector4<T> Vector4<T>::y_scale(T value) {
  return {T(1), value, T(1), T(1)};
}

template <typename T>
constexpr Vector4<T> Vector4<T>::z_scale(T value) {
  return {T(1), T(1), value, T(1)};
}

template <typename T>
constexpr Vector4<T> Vector4<T>::w_scale(T value) {
  return {T(1), T(1), T(1), value};
}

template <typename T>
constexpr Vector4<T>::Vector4() noexcept: Vector<4, T>() {}

template <typename T>
constexpr Vector4<T>::Vector4(std::initializer_list<T> list) noexcept: Vector<4, T>(list) {}

template <typename T>
constexpr Vector4<T>::Vector4(T value) noexcept: Vector<4, T>(value) {}

template <typename T>
constexpr Vector4<T>::Vector4(T x, T y, T z, T w) noexcept: Vector<4, T>{x, y, z, w} {}

template <typename T>
constexpr Vector4<T>::Vector4(const Vector3<T>& xyz, T w) noexcept: Vector<4, T>{xyz[0], xyz[1], xyz[2], w} {}

template <typename T>
constexpr Vector4<T>::Vector4(const Vector2<T>& xy, T z, T w) noexcept: Vector<4, T>{xy[0], xy[1], z, w} {}

template <typename T> template <std::size_t other_size, typename U>
constexpr Vector4<T>::Vector4(const Vector<other_size, U>& other) noexcept: Vector<4, T>(other) {}

template <typename T>
typename Vector4<T>::reference Vector4<T>::x() {
  return Vector<4, T>::data_[0];
}

template <typename T>
constexpr typename Vector4<T>::const_reference Vector4<T>::x() const {
  return Vector<4, T>::data_[0];
}

template <typename T>
typename Vector4<T>::reference Vector4<T>::y() {
  return Vector<4, T>::data_[1];
}

template <typename T>
constexpr typename Vector4<T>::const_reference Vector4<T>::y() const {
  return Vector<4, T>::data_[1];
}

template <typename T>
typename Vector4<T>::reference Vector4<T>::z() {
  return Vector<4, T>::data_[2];
}

template <typename T>
constexpr typename Vector4<T>::const_reference Vector4<T>::z() const {
  return Vector<4, T>::data_[2];
}

template <typename T>
typename Vector4<T>::reference Vector4<T>::w() {
  return Vector<4, T>::data_[3];
}

template <typename T>
Vector3<T>& Vector4<T>::xyz() {
  return Vector3<T>::from(Vector<4, T>::data());
}

template <typename T>
constexpr const Vector3<T> Vector4<T>::xyz() const {
  return {Vector<4, T>::data_[0], Vector<4, T>::data_[1], Vector<4, T>::data_[2]};
}

template <typename T>
constexpr typename Vector4<T>::const_reference Vector4<T>::w() const {
  return Vector<4, T>::data_[3];
}

template <typename T>
constexpr Vector4<T> Vector4<T>::Plane(const Vector3<T>& p0, const Vector3<T>& p1, const Vector3<T>& p2) {
  const Vector3<T> normal = Vector3<T>::CrossProduct(p1 - p0, p2 - p0).normalized();
  return {normal, -Vector<3, T>::DotProduct(normal, p0)};
}

template <typename T>
constexpr Vector4<T> Vector4<T>::Plane(const Vector3<T>& normal, const Vector3<T>& point) {
  return {normal, -Vector<3, T>::DotProduct(normal, point)};
}
