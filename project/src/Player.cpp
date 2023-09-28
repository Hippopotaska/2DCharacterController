#include "Player.h"

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

	// TODO: Change this to velocity instead of position
	if (inputMgr->IsKeyHeld(GLFW_KEY_A)) {
		mVelocity.x -= mMoveSpeed * deltaTime;
	}
	if (inputMgr->IsKeyHeld(GLFW_KEY_D)) {
		mVelocity.x += mMoveSpeed * deltaTime;
	}	
	if (inputMgr->IsKeyHeld(GLFW_KEY_S)) {
		mVelocity.y -= mMoveSpeed * deltaTime;
	}	
	if (inputMgr->IsKeyHeld(GLFW_KEY_W)) {
		mVelocity.y += mMoveSpeed * deltaTime;
	}

	*transform->GetPosition() += glm::vec3(mVelocity.x, mVelocity.y, 0.f);
	transform->Translate();

	GameObject::Update(deltaTime);
}