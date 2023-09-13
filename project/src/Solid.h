#pragma once

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

class Solid {
private:
	Transform mTransform;
	AABB mCollider;
	Sprite mSprite;

public:
	Solid(Transform nTransform, AABB nCollider, Sprite nSprite);
	~Solid();

	void Update(float deltaTime);

	Transform GetTransform();
	AABB GetCollider();
};