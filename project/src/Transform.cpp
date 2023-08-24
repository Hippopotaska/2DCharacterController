#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>

Transform::Transform() 
	: mPosition(glm::vec3(0)) {
	//mTransform = glm::translate();
}
Transform::Transform(glm::vec3 position) 
	: mPosition(position) {}
Transform::~Transform() {}

const glm::vec3& Transform::GetPosition() const {
	return mPosition;
}

void Transform::SetPosition(glm::vec3& newPos) {
	mPosition = newPos;
}