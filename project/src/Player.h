#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"

class Player : public GameObject {
private:
	float mMoveSpeed;
	glm::vec2 mVelocity;

	glm::vec3 mDefaultColor = glm::vec3(59, 150, 217);
	glm::vec3 mJumpColor = glm::vec3(59, 217, 84);

public:
	Player(Transform* nTransform, float nMoveSpeed);
	~Player();

	void Start();
	void Update(float deltaTime) override;
};