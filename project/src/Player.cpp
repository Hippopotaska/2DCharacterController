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

	// Calculating the gravity and jump power with max jump height and jump duration
	mGravity = -((8 * mMaxJumpHeight) / (mJumpDuration * mJumpDuration));
	mJumpPower = -(mGravity * (mJumpDuration * mJumpDuration)) * 0.5f;
}
Player::~Player() {}

void Player::Start() {}
void Player::Update(float deltaTime) {
	// TODO: Mechanics to implement
	// Jump buffering
	// Air controls

	auto inputMgr = InputManager::GetInstance();

	// Whenever the velocity values are change 
	// it needs to be multiplied by deltaTime

#pragma region Vertical Movement
	if (inputMgr->KeyHeld(GLFW_KEY_A)) {
		mVelocity.x -= mMoveSpeed * deltaTime;
		if (mVelocity.x < -mMaxMoveVelocity) {
			mVelocity.x = -mMaxMoveVelocity;
		}
	}
	if (inputMgr->KeyHeld(GLFW_KEY_D)) {
		mVelocity.x += mMoveSpeed * deltaTime;
		if (mVelocity.x > mMaxMoveVelocity) {
			mVelocity.x = mMaxMoveVelocity;
		}
	}
	if (!inputMgr->KeyHeld(GLFW_KEY_D) && !inputMgr->KeyHeld(GLFW_KEY_A)) {
		if (mVelocity.x > 0 && mVelocity.x != 0) {
			mVelocity.x -= mFriction * deltaTime;
			if (mVelocity.x < 0)
				mVelocity.x = 0;
		}
		if (mVelocity.x < 0 && mVelocity.x != 0) {
			mVelocity.x += mFriction * deltaTime;
			if (mVelocity.x > 0)
				mVelocity.x = 0;
		}
	}
#pragma endregion


	// Coyote time counter logic
	if (mGrounded) {
		mCoyoteTimeCounter = mCoyoteTime;
	} else {
		if (mCoyoteTimeCounter > 0) {
			mCoyoteTimeCounter -= deltaTime;
		} else {
			mCoyoteTimeCounter = 0;
		}
	}
	// Jump buffering counter logic
	// TODO: Jump buffering seems to work, but the jump force does not get applied
	// Most likely has something to do with collisions
	if (inputMgr->KeyPressed(GLFW_KEY_SPACE)) {
		mJumpBufferCounter = mJumpBufferTime;
	} else {
		if (mJumpBufferCounter > 0) {
			mJumpBufferCounter -= deltaTime;
		} else {
			mJumpBufferCounter = 0;
		}
	}

	if (mJumpBufferCounter > 0 && mCoyoteTimeCounter > 0) {
		mVelocity.y = mJumpPower;

		mJumpBufferCounter = 0;
		mCoyoteTimeCounter = 0;

		if (mGrounded)
			mGrounded = false;
	}

	if (inputMgr->KeyReleased(GLFW_KEY_SPACE) && mVelocity.y > 0) {
		mVelocity.y *= 0.5f;
	}

	if (!mGrounded) {
		mVelocity.y += mGravity * deltaTime;
		if (mVelocity.y < mMaxFall)
			mVelocity.y = mMaxFall;
	}


	mGrounded = false; 
	GameObject::Update(deltaTime);
}
void Player::LateUpdate(float deltaTime) {
	// Multiplying the velocity with delta AND Game scale for the CHANGE in position

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
		fix.y = (colInfo.intersectionDepth * 0.2f);
		fix.y *= colInfo.normal.y;
		mVelocity.y += mVelocity.y * -1;
	}
	else if (colInfo.normal.x != 0) { // Horizontal collision resolve
		fix.x = (colInfo.intersectionDepth * 0.2f);
		fix.x *= colInfo.normal.x;

		mVelocity.x += mVelocity.x * -1;
	}

	*transform->GetPosition() += fix;
	transform->Translate();
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