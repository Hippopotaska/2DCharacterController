#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"

class Player : public GameObject {
private:
	float mMoveSpeed;

public:
	Player(Transform* nTransform, float nMoveSpeed);
	~Player();

	void Start();
	void Update(float deltaTime) override;
};