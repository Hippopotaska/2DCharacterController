#pragma once

#include <glm/glm.hpp>

#include "Transform.h"
#include "AABB.h"

class Player {
private:
	class Transform mTransform;
	class AABB mCollider;

	float mMoveSpeed;

public:
	Player(Transform transform, AABB collider, float moveSpeed);
	~Player();

	void Start();
	void Update(float deltaTime);

	Transform GetTransform();
	AABB GetCollider();
};