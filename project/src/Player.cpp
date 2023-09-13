#include "Player.h"

#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include "Managers/InputManager.h"

Player::Player(Transform nTransform, AABB nCollider, Sprite nSprite, float nMoveSpeed) 
	: mTransform(nTransform), mCollider(nCollider), mSprite(nSprite), mMoveSpeed(nMoveSpeed) {}
Player::~Player() {}

void Player::Start() {}
void Player::Update(float deltaTime) {
	auto inputMgr = InputManager::GetInstance();

	// TODO: Change this to velocity instead of position
	if (inputMgr->IsKeyHeld(GLFW_KEY_A)) {
		mTransform.position.x -= mMoveSpeed * deltaTime;
	}
	if (inputMgr->IsKeyHeld(GLFW_KEY_D)) {
		mTransform.position.x += mMoveSpeed * deltaTime;
	}	
	if (inputMgr->IsKeyHeld(GLFW_KEY_S)) {
		mTransform.position.y -= mMoveSpeed * deltaTime;
	}	
	if (inputMgr->IsKeyHeld(GLFW_KEY_W)) {
		mTransform.position.y += mMoveSpeed * deltaTime;
	}

	mTransform.transform = glm::translate(glm::mat4(1.0f), mTransform.position);

	mCollider.SetPosition(mTransform.position);
	mSprite.SetPosition(mTransform.position);
	mSprite.Draw();
}

Transform Player::GetTransform() {
	return mTransform;
}
AABB Player::GetCollider() {
	return mCollider;
}