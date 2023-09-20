#include "AABB.h"

AABB::AABB(Transform nTransform, Transform* nParent, glm::vec2 nSize) 
	: mSize(nSize), Component(nTransform, nParent) {}
AABB::~AABB() {}

void AABB::Update(float deltaTime) {
	Component::Update(deltaTime);
}

float AABB::GetWidth() {
	return mSize.x;
}
float AABB::GetHeight() {
	return mSize.y;
}