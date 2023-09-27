#include "AABB.h"

AABB::AABB(Transform nTransform, Transform* nParent, glm::vec2 nSize) 
	: mSize(nSize), Component(nTransform, nParent) {
	min.x = nTransform.GetPosition()->x - nSize.x * 0.5f;
	min.y = nTransform.GetPosition()->y - nSize.y * 0.5f;
	max.x = nTransform.GetPosition()->x + nSize.x * 0.5f;
	max.y = nTransform.GetPosition()->y + nSize.y * 0.5f;
}
AABB::~AABB() {}

void AABB::Update(float deltaTime) {
	Component::Update(deltaTime);
	min.x = transform.GetPosition()->x - mSize.x * 0.5f;
	min.y = transform.GetPosition()->y - mSize.y * 0.5f;
	max.x = transform.GetPosition()->x + mSize.x * 0.5f;
	max.y = transform.GetPosition()->y + mSize.y * 0.5f;
}

float AABB::GetWidth() {
	return mSize.x;
}
float AABB::GetHeight() {
	return mSize.y;
}