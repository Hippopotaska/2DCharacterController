#include "Player.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

#include "Managers/InputManager.h"
#include "Managers/GameManager.h"

Player::Player(Transform* nTransform) 
	: mVelocity(glm::vec2(0.0f)) {
	transform = nTransform;
	AABB* collider = new AABB(*transform, transform, glm::vec2(100.0f));
	
	Shader* shader = new Shader("src/shaders/Basic.glsl");
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
		mVelocity.y = mJumpPower * deltaTime;
		mGrounded = false;
	}

	if (!mGrounded) {
		mVelocity.y += mGravity * deltaTime;
		if (mVelocity.y < mMaxFall)
			mVelocity.y = mMaxFall;
	}

	std::cout << "Velocity [" << mVelocity.x << ", " << mVelocity.y << "]" << std::endl;

	mGrounded = false; 
	// There is no simple way of adding another collider, 
	// so instead we make the player not grounded, so they fall for 1 frame
	// and check if there is ground under
	// Probably better solution would be to test with own collider if there is ground underneath
	// Like this; move collider down couple of pixels, if there is no ground then set mGrounded to be false
	GameObject::Update(deltaTime);
}
void Player::LateUpdate(float deltaTime) {
	*transform->GetPosition() += glm::vec3(mVelocity.x, mVelocity.y, 0.0f);
	transform->Translate();
}

void Player::OnCollide(CollisionInfo colInfo) {
	glm::vec3 fix = glm::vec3(0.0f);
	float delta = GameManager::GetInstance()->GetDeltaTime();

	if (colInfo.normal.y != 0) { // Vertical collision resolve
		if (colInfo.normal.y == 1) {
			if (!mGrounded)
				mGrounded = true;
		}
		fix.y = (colInfo.intersectionDepth * 0.2f);
		fix.y *= colInfo.normal.y;
		mVelocity.y += mVelocity.y * -1;
	}
	if (colInfo.normal.x != 0) { // Horizontal collision resolve
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