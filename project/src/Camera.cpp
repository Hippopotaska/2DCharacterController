#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
	: mProjectionMatrix(glm::mat4(1.0f)), mViewMatrix(glm::mat4(1.0f)), mProjectionViewMatrix(glm::mat4(1.0f))
	, mPosition(glm::vec3(0.0f)) {}

void Camera::Init(float left, float right, float bottom, float top) {
	mProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	RecalculateViewMatrix();
}

Camera* Camera::GetInstance() {
	if (!mInstance)
		mInstance = new Camera();
	return mInstance;
}

void Camera::RecalculateViewMatrix() {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition);

	mViewMatrix = glm::inverse(transform);
	mProjectionViewMatrix = mProjectionMatrix * mViewMatrix;
}