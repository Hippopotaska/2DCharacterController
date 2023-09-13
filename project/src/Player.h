#pragma once

#include <glm/glm.hpp>

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

class Player {
private:
	Transform mTransform;
	AABB mCollider;
	Sprite mSprite;

	float mMoveSpeed;

public:
	Player(Transform nTransform, AABB nCollider, Sprite nSprite, float nMoveSpeed);
	~Player();

	void Start();
	void Update(float deltaTime);

	Transform GetTransform();
	AABB GetCollider();
};