#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"

class Player : public GameObject {
private:
	glm::vec2 mVelocity = glm::vec2(0.0f);

	float mMaxJumpHeight = 2.f;
	float mJumpDuration = 1.f;

	bool mIsJumping = false;
	float mJumpTimer = 0.f;

	float mMaxFall = -6.f;

	float mJumpPower = 0.f;
	float mGravity = -0.f;

	float mMoveSpeed = 10.f;
	float mMaxMoveVelocity = 3.f;
	float mFriction = 15.f;

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