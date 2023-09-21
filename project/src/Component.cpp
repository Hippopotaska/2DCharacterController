#include "Component.h"

Component::Component(Transform nTransform, Transform* nParent)
	: transform(nTransform), mParent(nParent) {}
Component::~Component() {}

void Component::Update(float deltaTime) {
	if (mParent != nullptr) {
		transform.SetPosition(*mParent->GetPosition());
	}
}

Transform* Component::GetParent() {
	return mParent;
}
void Component::SetParent(Transform* newParent) {
	mParent = newParent;
}