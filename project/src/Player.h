#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"

class Player : public GameObject {
private:
	glm::vec2 mVelocity = glm::vec2(0.0f);

	float mGravity = -100.f;
	float mMaxFall = -2500.f;

	float mMoveSpeed = 0.f;
	float mJumpPower = 20000.f;

	bool mGrounded = false;

	glm::vec3 mDefaultColor = glm::vec3(59, 150, 217);
	glm::vec3 mJumpColor = glm::vec3(59, 217, 84);

public:
	Player(Transform* nTransform, float nMoveSpeed);
	~Player();

	void Start();
	void Update(float deltaTime) override;

	void OnCollide(struct CollisionInfo colInfo);
};