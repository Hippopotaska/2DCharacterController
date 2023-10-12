#include "AABB.h"

AABB::AABB () {}

AABB::AABB(Transform nTransform, Transform* nParent, glm::vec2 nSize, bool isStatic) 
	: mSize(nSize), mStatic(isStatic), Component(nTransform, nParent) {
	mSize.x *= transform.GetScale()->x;
	mSize.y *= transform.GetScale()->y;

	min.x = transform.GetPosition()->x - mSize.x * 0.5f;
	min.y = transform.GetPosition()->y - mSize.y * 0.5f;
	max.x = transform.GetPosition()->x + mSize.x * 0.5f;
	max.y = transform.GetPosition()->y + mSize.y * 0.5f;
}
AABB::~AABB() {}

void AABB::Update(float deltaTime) {
	if (!mStatic) {
		min.x = transform.GetPosition()->x - mSize.x * 0.5f;
		min.y = transform.GetPosition()->y - mSize.y * 0.5f;
		max.x = transform.GetPosition()->x + mSize.x * 0.5f;
		max.y = transform.GetPosition()->y + mSize.y * 0.5f;
	}

	Component::Update(deltaTime);
}