#include "Player.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

#include "Managers/InputManager.h"

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
	mVelocity = glm::vec2(0.0f);

	if (inputMgr->KeyHeld(GLFW_KEY_A)) {
		mVelocity.x -= mMoveSpeed;
	}
	if (inputMgr->KeyHeld(GLFW_KEY_D)) {
		mVelocity.x += mMoveSpeed;
	}	

	if (inputMgr->KeyPressed(GLFW_KEY_SPACE) && mGrounded) {
		mVelocity.y = mJumpPower;
		mGrounded = false;
	}

	if (!mGrounded) {
		mVelocity.y += mVelocity.y <= mMaxFall ? mMaxFall : mGravity;
	}


	*transform->GetPosition() += glm::vec3(mVelocity.x, mVelocity.y, 0.f) * deltaTime;
	transform->Translate();

	std::cout << "[" << transform->GetPosition()->x << ", " << transform->GetPosition()->y << "] - Grounded => " << mGrounded << std::endl;

	GameObject::Update(deltaTime);
}

void Player::OnCollide(CollisionInfo colInfo) {
	glm::vec3 fix = glm::vec3(mVelocity.x * 1.025f, mVelocity.y * 1.025f, 0);
	fix *= glm::vec3(colInfo.normal.x, colInfo.normal.y, 0);
	if (colInfo.normal.x == 1 || colInfo.normal.y == 1)
		fix *= -1.f; // TODO: This bugs me way too much. Needs to be researched if there is a fix.

	*transform->GetPosition() += fix;

	if (colInfo.normal.y == 1.0f && !mGrounded) {
		mGrounded = true;
	}
}