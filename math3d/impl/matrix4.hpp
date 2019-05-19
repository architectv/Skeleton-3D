template <typename T>
constexpr Matrix4<T> Matrix4<T>::translation(const Vector3<T>& vector) {
  return {{      T(1),       T(0),       T(0), T(0)},
          {      T(0),       T(1),       T(0), T(0)},
          {      T(0),       T(0),       T(1), T(0)},
          {vector.x(), vector.y(), vector.z(), T(1)}};
}

template <typename T>
constexpr Matrix4<T> Matrix4<T>::scaling(const Vector3<T>& vector) {
  return {{vector.x(),       T(0),       T(0), T(0)},
          {      T(0), vector.y(),       T(0), T(0)},
          {      T(0),       T(0), vector.z(), T(0)},
          {      T(0),       T(0),       T(0), T(1)}};
}

template <typename T> template <typename FloatingPoint>
std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix4<T>> Matrix4<T>::rotation(FloatingPoint angle, const Vector3<T>& normalized_axis) {
  assert(normalized_axis.IsNormalized());

  angle = ToRadians(angle);
  const T sine = std::sin(T(angle));
  const T cosine = std::cos(T(angle));
  const T one_minus_cosine = T(1) - cosine;

  const T xx = normalized_axis.x() * normalized_axis.x();
  const T xy = normalized_axis.x() * normalized_axis.y();
  const T xz = normalized_axis.x() * normalized_axis.z();
  const T yy = normalized_axis.y() * normalized_axis.y();
  const T yz = normalized_axis.y() * normalized_axis.z();
  const T zz = normalized_axis.z() * normalized_axis.z();

  return {
    {cosine + xx * one_minus_cosine,
     xy * one_minus_cosine + normalized_axis.z() * sine,
     xz * one_minus_cosine - normalized_axis.y() * sine,
     T(0)},
    {xy * one_minus_cosine - normalized_axis.z() * sine,
     cosine + yy * one_minus_cosine,
     yz * one_minus_cosine + normalized_axis.x() * sine,
     T(0)},
    {xz * one_minus_cosine + normalized_axis.y() * sine,
     yz * one_minus_cosine - normalized_axis.x() * sine,
     cosine + zz * one_minus_cosine,
     T(0)},
    {T(0), T(0), T(0), T(1)}
  };
}


template <typename T> template <typename FloatingPoint>
std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix4<T>> Matrix4<T>::rotation_x(FloatingPoint angle) {
  angle = ToRadians(angle);
  const T sine = std::sin(T(angle));
  const T cosine = std::cos(T(angle));

  return {{T(1),   T(0),   T(0), T(0)},
          {T(0), cosine,   sine, T(0)},
          {T(0),  -sine, cosine, T(0)},
          {T(0),   T(0),   T(0), T(1)}};
}

template <typename T> template <typename FloatingPoint>
std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix4<T>> Matrix4<T>::rotation_y(FloatingPoint angle) {
  angle = ToRadians(angle);
  const T sine = std::sin(T(angle));
  const T cosine = std::cos(T(angle));

  return {{cosine, T(0),  -sine, T(0)},
          {  T(0), T(1),   T(0), T(0)},
          {  sine, T(0), cosine, T(0)},
          {  T(0), T(0),   T(0), T(1)}};
}

template <typename T> template <typename FloatingPoint>
std::enable_if_t<std::is_floating_point<FloatingPoint>::value, Matrix4<T>> Matrix4<T>::rotation_z(FloatingPoint angle) {
  angle = ToRadians(angle);
  const T sine = std::sin(T(angle));
  const T cosine = std::cos(T(angle));

  return {{cosine,   sine, T(0), T(0)},
          { -sine, cosine, T(0), T(0)},
          {  T(0),   T(0), T(1), T(0)},
          {  T(0),   T(0), T(0), T(1)}};
}

template <typename T>
Matrix4<T> Matrix4<T>::reflection(const Vector3<T>& normal) {
  assert(normal.IsNormalized());
  return from(Matrix3x3<T>() - T(2)*normal * RectMatrix<1, 3, T>(normal).transposed());
}

template <typename T>
constexpr Matrix4<T> Matrix4<T>::shearing_xy(T amount_x, T amount_y) {
  return {{     (1),     T(0), T(0), T(0)},
          {     (0),     T(1), T(0), T(0)},
          {amount_x, amount_y, T(1), T(0)},
          {     (0),     T(0), T(0), T(1)}};
}

template <typename T>
constexpr Matrix4<T> Matrix4<T>::shearing_xz(T amount_x, T amount_z) {
  return {{    T(1), T(0),     T(0), T(0)},
          {amount_x, T(1), amount_z, T(0)},
          {    T(0), T(0),     T(1), T(0)},
          {    T(0), T(0),     T(0), T(1)}};
}

template <typename T>
constexpr Matrix4<T> Matrix4<T>::shearing_yz(T amount_y, T amount_z) {
  return {{T(1), amount_y, amount_z, T(0)},
          {T(0),     T(1),     T(0), T(0)},
          {T(0),     T(0),     T(1), T(0)},
          {T(0),     T(0),     T(0), T(1)}};
}

template <typename T>
Matrix4<T> Matrix4<T>::orthographic_projection(const Vector2<T>& size, const T near, const T far) {
  const Vector2<T> xy_scale = T(2.0) / size;
  const T z_scale = T(2.0) / (near-far);

  return {{xy_scale.x(),         T(0),                T(0), T(0)},
          {        T(0), xy_scale.y(),                T(0), T(0)},
          {        T(0),         T(0),             z_scale, T(0)},
          {        T(0),         T(0), near * z_scale-T(1), T(1)}};
}

template <typename T>
Matrix4<T> Matrix4<T>::perspective_projection(T fov, T aspect_ratio, T near, T far) {
  return perspective_projection(T(2) * near * std::tan(T(fov) * T(0.5)) * Vector2<T>::y_scale(T(1) / aspect_ratio), near, far);
}

template <typename T>
Matrix4<T> Matrix4<T>::perspective_projection(const Vector2<T>& size, const T near, const T far) {
  const Vector2<T> xy_scale = 2 * near / size;

  if(far == std::numeric_limits<T>::infinity()) {
    return {{xy_scale.x(),         T(0),                 T(0),  T(0)},
            {        T(0), xy_scale.y(),                 T(0),  T(0)},
            {        T(0),         T(0),                T(-1), T(-1)},
            {        T(0),         T(0),           T(-2)*near,  T(0)}};
  } else {
    const T z_scale = T(1.0) / (near - far);
    return {{xy_scale.x(),         T(0),                        T(0),  T(0)},
            {        T(0), xy_scale.y(),                        T(0),  T(0)},
            {        T(0),         T(0),      (far + near) * z_scale, T(-1)},
            {        T(0),         T(0), T(2) * far * near * z_scale,  T(0)}};
  }
}

template <typename T>
Matrix4<T> Matrix4<T>::look_at(const Vector3<T>& eye, const Vector3<T>& target, const Vector3<T>& up) {
  const Vector3<T> backward = (eye - target).normalized();
  const Vector3<T> right = Vector3<T>::CrossProduct(up, backward).normalized();
  const Vector3<T> real_up = Vector3<T>::CrossProduct(backward, right);
  return from({right, real_up, backward}, eye);
}

template<typename T>
Matrix3x3<T> Matrix4<T>::rotation() const {
  Matrix3x3<T> rotation{(*this)[0].xyz().normalized(),
                        (*this)[1].xyz().normalized(),
                        (*this)[2].xyz().normalized()};
  assert(rotation.IsOrthogonal());
  return rotation;
}

template <typename T>
Matrix3x3<T> Matrix4<T>::rotation_normalized() const {
  Matrix3x3<T> rotation{(*this)[0].xyz(),
                        (*this)[1].xyz(),
                        (*this)[2].xyz()};
  assert(rotation.IsOrthogonal());
  return rotation;
}


template <typename T>
constexpr Matrix4<T> Matrix4<T>::from(const Matrix3x3<T>& rotation_scaling, const Vector3<T>& translation) {
  return {{rotation_scaling[0], T(0)},
          {rotation_scaling[1], T(0)},
          {rotation_scaling[2], T(0)},
          {        translation, T(1)}};
}

template <typename T>
constexpr Matrix4<T>::Matrix4() noexcept: Matrix4x4<T>(typename Matrix4x4<T>::IdentityInitT()) {}

template <typename T>
constexpr Matrix4<T>::Matrix4(T value) noexcept: Matrix4x4<T>(value) {}

template <typename T>
constexpr Matrix4<T>::Matrix4(typename Matrix<4, T>::IdentityInitT t, T value) noexcept: Matrix4x4<T>(t, value) {}

template <typename T>
constexpr Matrix4<T>::Matrix4(const Vector4<T>& first, const Vector4<T>& second, const Vector4<T>& third, const Vector4<T>& fourth) noexcept
    : Matrix4x4<T>(first, second, third, fourth) {}

template <typename T> template <std::size_t cols, std::size_t rows, typename U>
constexpr Matrix4<T>::Matrix4(const RectMatrix<cols, rows, U>& other) noexcept: Matrix4x4<T>(other) {}

template <typename T>
bool Matrix4<T>::IsRigidTransformation() const {
  return rotation_scaling().IsOrthogonal() && Matrix4x4<T>::row(3) == Vector4<T>(T(0), T(0), T(0), T(1));
}

template <typename T>
constexpr Matrix3x3<T> Matrix4<T>::rotation_scaling() const {
  return {(*this)[0].xyz(),
          (*this)[1].xyz(),
          (*this)[2].xyz()};
}

template <typename T>
constexpr Matrix3x3<T> Matrix4<T>::rotation_shear() const {
  return {(*this)[0].xyz().normalized(),
          (*this)[1].xyz().normalized(),
          (*this)[2].xyz().normalized()};
}

template <typename T>
Vector3<T> Matrix4<T>::scaling_squared() const {
  return {(*this)[0].xyz().dot(),
          (*this)[1].xyz().dot(),
          (*this)[2].xyz().dot()};
}

template <typename T>
Vector3<T> Matrix4<T>::scaling() const {
  return {(*this)[0].xyz().length(),
          (*this)[1].xyz().length(),
          (*this)[2].xyz().length()};
}

template <typename T>
T Matrix4<T>::uniform_scaling() const {
  return std::sqrt(uniform_scaling_squared());
}

template <typename T>
Vector3<T>& Matrix4<T>::right() {
  return (*this)[0].xyz();
}

template <typename T>
constexpr Vector3<T> Matrix4<T>::right() const {
  return (*this)[0].xyz();
}

template <typename T>
Vector3<T>& Matrix4<T>::up() {
  return (*this)[1].xyz();
}

template <typename T>
constexpr Vector3<T> Matrix4<T>::up() const {
  return (*this)[1].xyz();
}

template <typename T>
Vector3<T>& Matrix4<T>::backward() {
  return (*this)[2].xyz();
}

template <typename T>
constexpr Vector3<T> Matrix4<T>::backward() const {
  return (*this)[2].xyz();
}

template <typename T>
Vector3<T>& Matrix4<T>::translation() {
  return (*this)[3].xyz();
}

template <typename T>
constexpr Vector3<T> Matrix4<T>::translation() const {
  return (*this)[3].xyz();
}

template <typename T>
T Matrix4<T>::uniform_scaling_squared() const {
  const T scaling_squared = (*this)[0].xyz().dot();
  assert(TypeTraits<T>::equals((*this)[1].xyz().dot(), scaling_squared) && TypeTraits<T>::equals((*this)[2].xyz().dot(), scaling_squared));
  return scaling_squared;
}

template <typename T> Matrix4<T> Matrix4<T>::inverted_rigid() const {
  assert(IsRigidTransformation());
  const Matrix3x3<T> inverse_rotation = rotation_scaling().transposed();
  return from(inverse_rotation, inverse_rotation * -translation());
}


template <typename T>
Vector3<T> Matrix4<T>::map_vector(const Vector3<T>& vector) const {
  return ((*this) * Vector4<T>(vector, T(0))).xyz();
}

template <typename T>
Vector3<T> Matrix4<T>::map_point(const Vector3<T>& vector) const {
  const Vector4<T> transformed{(*this) * Vector4<T>(vector, T(1))};
  return transformed.xyz() / transformed.w();
}

