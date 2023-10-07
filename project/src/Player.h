#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"

class Player : public GameObject {
private:
	glm::vec2 mVelocity = glm::vec2(0.0f);

	static constexpr float GAME_SCALE = 100;

	float mGravity = -8.f * GAME_SCALE;
	float mMaxFall = -4.f * GAME_SCALE;
	float mJumpPower = 6.f * GAME_SCALE;

	float mMoveSpeed = 2.5f * GAME_SCALE;
	float mMaxMoveVelocity = 5.f * GAME_SCALE;
	float mFriction = 4.f * GAME_SCALE;

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