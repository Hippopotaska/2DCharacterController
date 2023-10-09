#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"

class Player : public GameObject {
private:
	glm::vec2 mVelocity = glm::vec2(0.0f);

	float mGravity = -8.f;
	float mMaxFall = -4.f;
	float mJumpPower = 9.f;

	float mMoveSpeed = 5.f;
	float mMaxMoveVelocity = 3.f;
	float mFriction = 8.f;

	bool mGrounded = false;

	float mResetTime = 1.f;
	float mCurTimer = 0;
	bool mReset = false;

	glm::vec3 mDefaultColor = glm::vec3(59, 150, 217);
	glm::vec3 mJumpColor = glm::vec3(59, 217, 84);

public:
	Player(glm::vec3 pos);
	~Player();

	void Start();
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;

	void OnCollide(struct CollisionInfo colInfo);

	glm::vec3 GetMoveDirection();
	glm::vec3 GetVelocity();
};