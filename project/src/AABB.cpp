#include "AABB.h"

AABB::AABB(Transform transform) 
	: mTransform(transform) {}
AABB::~AABB() {}

void AABB::Update(float deltaTime) {
	// Collision checks
	// How to check collision with another object
}