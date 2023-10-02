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

	mGrounded = false; 
	// There is no simple way of adding another trigger type collider, 
	// so instead we make the player not grounded, so they fall for 1 frame
	// and check if there is ground under
	GameObject::Update(deltaTime);
}
void Player::LateUpdate(float deltaTime) {
	*transform->GetPosition() += glm::vec3(mVelocity.x * deltaTime, mVelocity.y * deltaTime, 0.0f);
	transform->Translate();

	nextPos = *transform->GetPosition() + glm::vec3(mVelocity.x * deltaTime, mVelocity.y * deltaTime, 0.0f);
}

void Player::OnCollide(CollisionInfo colInfo) {
	glm::vec3 fix = glm::vec3(0.0f);
	float delta = GameManager::GetInstance()->GameTime->delta;

	// NOTE: The issue now seems to be that the intersection depth isn't calculated properly, causing the object to
	// be pushed way further than necessary. Other might be the velocity; having the objects not colliding at all would be the best
	// since that would seem the cleanest to the user. This would need to be checked with players *NEXT position and then checking with that
	// 
	// TODO: Change it so that we check collision with players future position and not current position
	// with this we can move the player next to the collision object.

	if (colInfo.normal.y != 0) { // Vertical collision resolve
		if (colInfo.normal.y == 1) {
			if (!mGrounded)
				mGrounded = true;
		}
		fix.y = colInfo.intersectionDepth *  0.375f;
		fix.y *= colInfo.normal.y;
		mVelocity.y = 0;
	}
	if (colInfo.normal.x != 0) { // Horizontal collision resolve
		fix.x =  colInfo.intersectionDepth *  0.375f;
		fix.x *= colInfo.normal.x;
		mVelocity.x = 0;
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