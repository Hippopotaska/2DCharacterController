#pragma once

#include <glm/glm.hpp>

#include "Transform.h"
#include "AABB.h"

class Player {
private:
	Transform mTransform;
	AABB mCollider;

	float mMoveSpeed;

public:
	Player(Transform transform, AABB collider, float moveSpeed);
	~Player();

	void Start();
	void Update(float deltaTime);
};