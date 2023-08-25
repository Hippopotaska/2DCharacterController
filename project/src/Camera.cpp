#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float left, float right, float bottom, float top) 
	: mProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), mViewMatrix(1.0f), mPosition(glm::vec3(0.0f)) {
	mProjectionViewMatrix = mProjectionMatrix * mViewMatrix;
}

void Camera::RecalculateViewMatrix() {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition);

	mViewMatrix = glm::inverse(transform);
	mProjectionViewMatrix = mProjectionMatrix * mViewMatrix;
}