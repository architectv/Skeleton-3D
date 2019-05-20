template <typename T>
constexpr Matrix3<T> Matrix3<T>::translation(const Vector2<T> &vector) {
  return {{      T(1),       T(0), T(0)},
          {      T(0),       T(1), T(0)},
          {vector.x(), vector.y(), T(1)}};
}

template <typename T>
constexpr Matrix3<T> Matrix3<T>::scaling(const Vector2<T> &vector) {
  return {{vector.x(),       T(0), T(0)},
          {      T(0), vector.y(), T(0)},
          {      T(0),       T(0), T(1)}};
}

template <typename T> Matrix2x2<T> Matrix3<T>::rotation() const {
  Matrix2x2<T> rotation{(*this)[0].xy().normalized(),
                        (*this)[1].xy().normalized()};
  assert(rotation.IsOrthogonal());
  return rotation;
}

template <typename T>
Matrix3<T> Matrix3<T>::reflection(const Vector2<T> &normal) {
  assert(normal.IsNormalized());
  return from(Matrix2x2<T>() - T(2) * normal * RectMatrix<1, 2, T>(normal).transposed(), {});
}

template <typename T>
constexpr Matrix3<T> Matrix3<T>::shearing_x(T amount) {
  return {{  T(1), T(0), T(0)},
          {amount, T(1), T(0)},
          {  T(0), T(0), T(1)}};
}
template <typename T>
constexpr Matrix3<T> Matrix3<T>::shearing_y(T amount) {
  return {{T(1), amount, T(0)},
          {T(0),   T(1), T(0)},
          {T(0),   T(0), T(1)}};
}

template <typename T>
Matrix3<T> Matrix3<T>::projection(const Vector2<T> &size) {
  return scaling(2.0f/size);
}

template <typename T>
constexpr Matrix3<T> Matrix3<T>::from(const Matrix2x2<T> &rotation_scaling, const Vector2<T> &translation) {
  return {{rotation_scaling[0], T(0)},
          {rotation_scaling[1], T(0)},
          {        translation, T(1)}};
}

template <typename T>
constexpr Matrix3<T>::Matrix3() noexcept: Matrix3x3<T>(typename Matrix3x3<T>::IdentityInitT()) {}

template <typename T>
constexpr Matrix3<T>::Matrix3(T value) noexcept: Matrix3x3<T>(value) {}

template <typename T>
constexpr Matrix3<T>::Matrix3(typename Matrix<3, T>::IdentityInitT t, T value) noexcept: Matrix3x3<T>(t, value) {}

template <typename T>
constexpr Matrix3<T>::Matrix3(const Vector3<T>& first, const Vector3<T>& second, const Vector3<T>& third) noexcept
    : Matrix3x3<T>(first, second, third) {}

template <typename T> template <std::size_t cols, std::size_t rows, typename U>
constexpr Matrix3<T>::Matrix3(const RectMatrix<cols, rows, U>& other) noexcept: Matrix3x3<T>(other) {}

template <typename T>
bool Matrix3<T>::IsRigidTransformation() const {
  return rotation_scaling().IsOrthogonal() && this->row(2) == Vector3<T>(T(0), T(0), T(1));
}

template <typename T>
constexpr Matrix2x2<T> Matrix3<T>::rotation_scaling() const {
  return {(*this)[0].xy(),
          (*this)[1].xy()};
}

template <typename T>
Matrix2x2<T> Matrix3<T>::rotation_shear() const {
  return {(*this)[0].xy().normalized(),
          (*this)[1].xy().normalized()};
}

template <typename T> template <typename FloatingPoint>
std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix3<T>> Matrix3<T>::rotation(FloatingPoint angle) {
  angle = ToRadians(angle);
  const T sine = std::sin(T(angle));
  const T cosine = std::cos(T(angle));

  return {{ cosine,   sine, T(0)},
          {  -sine, cosine, T(0)},
          {   T(0),   T(0), T(1)}};
}

template <typename T> Matrix2x2<T> Matrix3<T>::rotation_normalized() const {
  Matrix2x2<T> rotation{(*this)[0].xy(),
                        (*this)[1].xy()};
  assert(rotation.IsOrthogonal());
  return rotation;
}

template <typename T>
Vector2<T> Matrix3<T>::scaling_squared() const {
  return {(*this)[0].xy().dot(),
          (*this)[1].xy().dot()};
}

template <typename T>
Vector2<T> Matrix3<T>::scaling() const {
  return {(*this)[0].xy().length(),
          (*this)[1].xy().length()};
}

template <typename T> T Matrix3<T>::uniform_scaling_squared() const {
  const T scaling_squared = (*this)[0].xy().dot();
  assert(TypeTraits<T>::equals((*this)[1].xy().dot(), scaling_squared));
  return scaling_squared;
}

template <typename T>
T Matrix3<T>::uniform_scaling() const {
  return std::sqrt(uniform_scaling_squared());
}

template <typename T>
Vector2<T> &Matrix3<T>::right() {
  return (*this)[0].xy();
}

template <typename T>
constexpr Vector2<T> Matrix3<T>::right() const {
  return (*this)[0].xy();
}

template <typename T>
Vector2<T> &Matrix3<T>::up() {
  return (*this)[1].xy();
}

template <typename T>
constexpr Vector2<T> Matrix3<T>::up() const {
  return (*this)[1].xy();
}

template <typename T>
Vector2<T> &Matrix3<T>::translation() {
  return (*this)[2].xy();
}

template <typename T>
constexpr Vector2<T> Matrix3<T>::translation() const {
  return (*this)[2].xy();
}

template <typename T>
Matrix3<T> Matrix3<T>::inverted_rigid() const {
  assert(IsRigidTransformation());
  Matrix2x2<T> inverse_rotation = rotation_scaling().transposed();
  return from(inverse_rotation, inverse_rotation * -translation());
}

template <typename T>
Vector2<T> Matrix3<T>::map_vector(const Vector2<T> &vector) const {
  return (Vector3<T>((*this) * Vector3<T>(vector, T(0)))).xy();
}

template<typename T>
Vector2<T> Matrix3<T>::map_point(const Vector2<T> &vector) const {
  return (Vector3<T>((*this) * Vector3<T>(vector, T(1)))).xy();
}
