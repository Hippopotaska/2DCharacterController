#pragma once

#include "Component.h"
#include "Transform.h"

class AABB : Component{
private:
	Transform mTransform;
public:
	AABB(Transform transform);
	~AABB();

	void Update(float deltaTime) override;
};