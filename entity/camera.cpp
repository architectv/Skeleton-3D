#include "camera.hpp"

Camera::Camera() : view_direction_(0.0f, 0.0f, -1.0f) {}

Matrix Camera::world_to_view() const {
	return Matrix::lookAt(position_, position_ + view_direction_, Point(0.0f, 1.0f, 0.0f);
}
