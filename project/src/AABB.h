#pragma once

#include "Transform.h"

class AABB {
private:
	Transform mTransform;
public:
	AABB(Transform transform);
	~AABB();

	void Update(float deltaTime);
};