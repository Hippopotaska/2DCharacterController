#pragma once

#include <glm/glm.hpp>

#include "GameObject.h"

class Player : public GameObject {
private:
	glm::vec2 mVelocity = glm::vec2(0.0f);

	float mCoyoteTimeCounter = 0.f;
	float mJumpBufferCounter = 0.f;
	
	float mJumpPower = 0.f;
	float mGravity = -0.f;

	bool mGrounded = false;

	glm::vec3 mDefaultColor = glm::vec3(59, 150, 217);
	glm::vec3 mJumpColor = glm::vec3(59, 217, 84);

public:
	float maxJumpHeight = 2.f;
	float jumpDuration = 1.f;

	float coyoteTime = 0.15f;
	float jumpBufferTime = 0.1f;

	float maxFall = -6.f;

	float moveSpeed = 10.f;
	float maxMoveVelocity = 3.f;
	float friction = 15.f;
	float airFriction = 5.f;

	float airControlMult = 0.85f;
	float variableJumpMult = 0.65f;

	Player(glm::vec3 pos);
	~Player();

	void Start();
	void Update(float deltaTime) override;
	void LateUpdate(float deltaTime) override;

	void OnCollide(struct CollisionInfo colInfo);

	void CalcGravityAndJumpPower();

	glm::vec3 GetMoveDirection();
	glm::vec3 GetVelocity();
};