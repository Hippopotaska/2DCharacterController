#include "Player.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

#include "Managers/CollisionManager.h"
#include "Managers/InputManager.h"
#include "Managers/GameManager.h"

// Change so that takes no transform in as parameter
Player::Player(glm::vec3 pos) 
	: mVelocity(glm::vec2(0.0f)) {
	transform = new Transform(glm::mat4(1.0f), pos, glm::vec3(1.0f));
	AABB* collider = new AABB(*transform, transform, glm::vec2(100.0f), false);
	
	Shader* shader = new Shader("src/shaders/Player.glsl");
	Texture* texture = new Texture("res/textures/Pixel.png");
	Sprite* sprite = new Sprite(shader, texture, mDefaultColor, *transform, transform);

	AddComponent(collider);
	AddComponent(sprite);

	collider->SetParent(transform);
	sprite->SetParent(transform);

	CalcGravityAndJumpPower();
}
Player::~Player() {}

void Player::Start() {}
void Player::Update(float deltaTime) {
	auto inputMgr = InputManager::GetInstance();

#pragma region Vertical Movement
	if (inputMgr->KeyHeld(Keyboard_A)) {
		if (mGrounded)
			mVelocity.x -= moveSpeed * deltaTime;
		else
			mVelocity.x -= moveSpeed * deltaTime * airControlMult;

		if (mVelocity.x < -maxMoveVelocity) {
			mVelocity.x = -maxMoveVelocity;
		}
	}
	if (inputMgr->KeyHeld(Keyboard_D)) {
		if (mGrounded)
			mVelocity.x += moveSpeed * deltaTime;
		else
			mVelocity.x += moveSpeed * deltaTime * airControlMult;

		if (mVelocity.x > maxMoveVelocity) {
			mVelocity.x = maxMoveVelocity;
		}
	}
	if (!inputMgr->KeyHeld(Keyboard_D) && !inputMgr->KeyHeld(Keyboard_A)) {
		if (mVelocity.x > 0 && mVelocity.x != 0) {
			if (mGrounded)
				mVelocity.x -= friction * deltaTime;
			else
				mVelocity.x -= airFriction * deltaTime;

			if (mVelocity.x < 0)
				mVelocity.x = 0;
		}
		if (mVelocity.x < 0 && mVelocity.x != 0) {
			if (mGrounded)
				mVelocity.x += friction * deltaTime;
			else 
				mVelocity.x += airFriction * deltaTime;

			if (mVelocity.x > 0)
				mVelocity.x = 0;
		}
	}
#pragma endregion
#pragma region Jump timers logic
	// Coyote time
	if (mGrounded) {
		mCoyoteTimeCounter = coyoteTime;
	} else {
		if (mCoyoteTimeCounter > 0) {
			mCoyoteTimeCounter -= deltaTime;
		} else {
			mCoyoteTimeCounter = 0;
		}
	}

	// Jump buffering
	if (inputMgr->KeyHeld(Keyboard_Space)) {
		mJumpBufferCounter = jumpBufferTime;
	}
	else {
		if (mJumpBufferCounter > 0) {
			mJumpBufferCounter -= deltaTime;
		}
		else {
			mJumpBufferCounter = 0;
		}
	}
#pragma endregion

	mGrounded = false;
	GameObject::Update(deltaTime);
}
void Player::LateUpdate(float deltaTime) {
	auto inputMgr = InputManager::GetInstance();

	if (mJumpBufferCounter > 0 && mCoyoteTimeCounter > 0) {
		mVelocity.y = mJumpPower;

		mCoyoteTimeCounter = 0;
		mJumpBufferCounter = 0;

		mGrounded = false;
	}

	if (inputMgr->KeyReleased(Keyboard_Space) && mVelocity.y > 0) {
		mVelocity.y *= variableJumpMult;
	}

	if (!mGrounded) {
		mVelocity.y += mGravity * deltaTime;
		if (mVelocity.y < maxFall)
			mVelocity.y = maxFall;
	}

	deltaTime *= GameManager::GAME_SCALE;
	*transform->GetPosition() += glm::vec3(mVelocity.x * deltaTime, mVelocity.y * deltaTime, 0.0f);
	transform->Translate();
}

void Player::OnCollide(CollisionInfo colInfo) {
	glm::vec3 fix = glm::vec3(0.0f);

	if (colInfo.normal.y != 0) { // Vertical collision resolve
		if (colInfo.normal.y == 1) {
			if (!mGrounded) {
				mGrounded = true;
			}
		}
		fix.y = (colInfo.intersectionDepth * 0.35f);
		fix.y *= colInfo.normal.y;

		if (mVelocity.y <= 0 || colInfo.normal.y == -1)
			mVelocity.y = 0;
	}
	else if (colInfo.normal.x != 0) { // Horizontal collision resolve
		fix.x = (colInfo.intersectionDepth * 0.35f);
		fix.x *= colInfo.normal.x;

		mVelocity.x = 0;
	}

	*transform->GetPosition() += fix;
	transform->Translate();
}

void Player::ResetStats() {
	maxJumpHeight = 2.f;
	jumpDuration = 0.5f;

	coyoteTime = 0.15f;
	jumpBufferTime = 0.1f;

	maxFall = -6.f;

	moveSpeed = 10.f;
	maxMoveVelocity = 3.f;
	friction = 15.f;
	airFriction = 5.f;

	airControlMult = 0.85f;
	variableJumpMult = 0.65f;

	CalcGravityAndJumpPower();

	transform->SetPosition(glm::vec3(0.0f));
}
void Player::CalcGravityAndJumpPower() {
	mGravity = -(2 * maxJumpHeight) / (jumpDuration * jumpDuration);
	mJumpPower = -mGravity * (jumpDuration);
}

glm::vec3 Player::GetMoveDirection() {
	glm::vec2 norm = glm::vec2(0.0f);
	if (mVelocity.x != 0 || mVelocity.y != 0) {
		norm = glm::normalize(mVelocity);
	}
	return glm::vec3(norm.x, norm.y, 0.f);
}
glm::vec3 Player::GetVelocity() {
	return glm::vec3(mVelocity.x, mVelocity.y, 0.0f);
}