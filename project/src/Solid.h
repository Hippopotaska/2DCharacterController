#pragma once

#include "Transform.h"
#include "AABB.h"

class Solid {
private:
	Transform mTransform;
	AABB mCollider;

public:
	Solid(Transform nTransform, AABB nCollider);
	~Solid();

	Transform GetTransform();
	AABB GetCollider();
};