#include "Component.h"

Component::Component(Transform nTransform, Transform* nParent)
	: mTransform(nTransform), mParent(nParent) {}
Component::~Component() {}

void Component::Update(float deltaTime) {
	if (mParent != nullptr) {
		SetPosition(mParent->position);
	}
}

glm::vec3 Component::GetPosition() {
	return mTransform.position;
}
void Component::SetPosition(glm::vec3 newPos) {
	mTransform.position = newPos;
	mTransform.transform = glm::translate(glm::mat4(1.0f), mTransform.position);
}
Transform Component::GetTransform() {
	return mTransform;
}

Transform* Component::GetParent() {
	return mParent;
}
void Component::SetParent(Transform* newParent) {
	mParent = newParent;
}