#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"

class Player : public GameObject {
private:
	glm::vec2 mVelocity = glm::vec2(0.0f);

	float mGravity = -8.5f;
	float mMaxFall = -350.f;
	float mJumpPower = 450.f;

	float mMoveSpeed = 250.f;
	float mMaxMoveVelocity = 2.f;
	float mFriction = 1500.f;

	bool mGrounded = false;

	float mResetTime = 1.f;
	float mCurTimer = 0;
	bool mReset = false;

	glm::vec3 mDefaultColor = glm::vec3(59, 150, 217);
	glm::vec3 mJumpColor = glm::vec3(59, 217, 84);

public:
	Player(Transform* nTransform);
	~Player();

	void Start();
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;

	void OnCollide(struct CollisionInfo colInfo);

	glm::vec3 GetMoveDirection();
	glm::vec3 GetVelocity();
};