#include "Component.h"

Component::Component() {}
Component::Component(Transform nTransform, Transform* nParent)
	: transform(nTransform), mParent(nParent) {}
Component::~Component() {}

void Component::Update(float deltaTime) {
	if (mParent != nullptr) {
		transform.SetPosition(*mParent->GetPosition());
	}
}
void Component::LateUpdate(float deltaTime) {}

Transform* Component::GetParent() {
	return mParent;
}
void Component::SetParent(Transform* newParent) {
	mParent = newParent;
}