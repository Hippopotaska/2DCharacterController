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
}
Player::~Player() {}

void Player::Start() {}
void Player::Update(float deltaTime) {
	// TODO: Mechanics to implement
	// Coyote time
	// Jump buffering
	// Variable jump height
	// Air controls

	auto inputMgr = InputManager::GetInstance();
	// Multiplying CHANGES to velocity with delta

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
		if (mVelocity.x != 0) {
			if (mVelocity.x > 0) {
				mVelocity.x -= mFriction * deltaTime;
				if (mVelocity.x < 0)
					mVelocity.x = 0;
			}
			else if (mVelocity.x < 0) {
				mVelocity.x += mFriction * deltaTime;
				if (mVelocity.x > 0)
					mVelocity.x = 0;
			}
		}
	}

	if (inputMgr->KeyHeld(GLFW_KEY_R)) {
		if (!mReset) {
			mCurTimer += deltaTime;
			if (mCurTimer >= mResetTime) {
				transform->SetPosition(glm::vec3(0,0,0));
				mVelocity = glm::vec3(0.0f);

				mReset = true;
				mCurTimer = 0;
			}
		}
	}
	else {
		mReset = false;
		mCurTimer = 0;
	}

	if (inputMgr->KeyPressed(GLFW_KEY_SPACE) && mGrounded) {
		this->GetComponent<Sprite>()->SetColor(mJumpColor, 1);
		mVelocity.y = mJumpPower;
		mGrounded = false;
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
			if (!mGrounded)
				this->GetComponent<Sprite>()->SetColor(mDefaultColor, 1);
				mGrounded = true;
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