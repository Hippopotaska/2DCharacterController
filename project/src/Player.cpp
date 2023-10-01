#include "Player.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

#include "Managers/InputManager.h"
#include "Managers/GameManager.h"

Player::Player(Transform* nTransform, float nMoveSpeed) 
	: mMoveSpeed(nMoveSpeed), mVelocity(glm::vec2(0.0f)) {
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
	auto inputMgr = InputManager::GetInstance();

	if (inputMgr->KeyHeld(GLFW_KEY_A)) {
		mVelocity.x -= mMoveSpeed;
		if (mVelocity.x < -mMaxMoveVelocity) {
			mVelocity.x = -mMaxMoveVelocity;
		}
	}
	if (inputMgr->KeyHeld(GLFW_KEY_D)) {
		mVelocity.x += mMoveSpeed;
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
		mVelocity.y = mJumpPower;
		mGrounded = false;
	}

	if (!mGrounded) {
		mVelocity.y += mGravity;
		if (mVelocity.y < mMaxFall)
			mVelocity.y = mMaxFall;
	}


	//*transform->GetPosition() += glm::vec3(mVelocity.x * deltaTime, mVelocity.y * deltaTime, 0.f);
	//transform->Translate();

	std::cout << "Velocity [" << mVelocity.x << ", " << mVelocity.y << "]" << std::endl;

	GameObject::Update(deltaTime);
	mGrounded = false; 
	// There is no simple way of adding another trigger type collider, 
	// so instead we make the player not grounded, so they fall for 1 frame
	// and check if there is ground under
}
void Player::LateUpdate(float deltaTime) {
	*transform->GetPosition() += glm::vec3(mVelocity.x * deltaTime, mVelocity.y * deltaTime, 0.0f);
	transform->Translate();
}

void Player::OnCollide(CollisionInfo colInfo) {
	glm::vec3 fixVec = glm::vec3(0.0f);
	float delta = GameManager::GetInstance()->GameTime->delta;

	if (colInfo.normal.x != 0) { // Horizontal collision
		fixVec.x = colInfo.intersectionDepth * colInfo.normal.x + mVelocity.x * -1;
		mVelocity.x = 0;
	}
	else if (colInfo.normal.y != 0) { // Vertical collision
		float yVal = colInfo.normal.y == 1.0f ? colInfo.collidedObject.max.y : colInfo.collidedObject.min.y;
		fixVec.y = colInfo.intersectionDepth * colInfo.normal.y + mVelocity.y * -1;
		if (colInfo.normal.y == 1.0f && !mGrounded) {
			mGrounded = true;
		}
		mVelocity.y = 0;
	}
	
	mVelocity.y += fixVec.y;
	mVelocity.x += fixVec.x;

	//glm::vec3 fix = glm::vec3(0.0f);
	//float delta = GameManager::GetInstance()->GameTime->delta;

	//if (colInfo.normal.y != 0) { // Vertical collision resolve
	//	if (colInfo.normal.y == 1) {
	//		fix.y = mVelocity.y + colInfo.intersectionDepth;
	//		if (!mGrounded)
	//			mGrounded = true;
	//	} else {
	//		fix.y = mVelocity.y - colInfo.intersectionDepth;
	//	}
	//	fix.y *= colInfo.normal.y;
	//	mVelocity.y = 0;
	//}
	//if (colInfo.normal.x != 0) { // Horizontal collision resolve
	//	if (colInfo.normal.x == 1) {
	//		fix.x = mVelocity.x + colInfo.intersectionDepth;
	//	} else {
	//		fix.x = -mVelocity.x - colInfo.intersectionDepth;
	//	}
	//	fix.x *= colInfo.normal.x;
	//	mVelocity.x = 0;
	//}

	//mVelocity.y += fix.y;
	//mVelocity.x += fix.x;
}