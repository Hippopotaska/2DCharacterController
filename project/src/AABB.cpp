#include "AABB.h"

AABB::AABB(Transform nTransform, glm::vec2 nSize) 
	: mTransform(nTransform), mSize(nSize) {}
AABB::~AABB() {}

void AABB::Update(float deltaTime) {}
void AABB::SetPosition(glm::vec3 newPos) {
	mTransform.position = newPos;
}

glm::vec3 AABB::GetPosition() {
	return mTransform.position;
}

float AABB::GetWidth() {
	return mSize.x;
}
float AABB::GetHeight() {
	return mSize.y;
}