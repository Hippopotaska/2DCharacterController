#include "Transform.h"

Transform::Transform() {
	Init(glm::mat4(1.0f), glm::vec3(0.0f), glm::vec3(1.0f));
}
Transform::Transform(Transform& nTransform) {
	Init(*nTransform.GetTransform(), *nTransform.GetPosition(), *nTransform.GetScale());
}
Transform::Transform(glm::mat4 nTransform, glm::vec3 nPosition, glm::vec3 nScale) {
	Init(nTransform, nPosition, nScale);
}

void Transform::Init(glm::mat4 nTransform, glm::vec3 nPosition, glm::vec3 nScale) {
	mTransform = nTransform;
	mPosition = nPosition;
	mScale = nScale;

	Translate();
}

void Transform::Translate() {
	mTransform = glm::translate(glm::mat4(1.0f), mPosition);
	mTransform = glm::scale(mTransform, mScale);
}

glm::mat4* Transform::GetTransform() {
	return &mTransform;
}
void Transform::SetTransform(glm::mat4 newTransform) {
	mTransform = newTransform;
}

glm::vec3* Transform::GetPosition() {
	return &mPosition;
}
void Transform::SetPosition(glm::vec3 newPosition) {
	mPosition = newPosition;
	Translate();
}

glm::vec3* Transform::GetScale() {
	return &mScale;
}
void Transform::SetScale(glm::vec3 nScale) {
	mScale = nScale;
	Translate();
}