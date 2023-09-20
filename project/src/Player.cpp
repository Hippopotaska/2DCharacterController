#include "Player.h"

#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include "Transform.h"
#include "AABB.h"
#include "Sprite.h"

#include "Managers/InputManager.h"

Player::Player(Transform* nTransform, float nMoveSpeed) 
	: mMoveSpeed(nMoveSpeed) {
	SetTransform(nTransform);
	Transform* transform = GetTransform();

	AABB* collider = new AABB(*GetTransform(), transform, glm::vec2(100.0f));
	
	Shader* shader = new Shader("src/shaders/Basic.glsl");
	Texture* texture = new Texture("res/textures/Pixel.png");
	Sprite* sprite = new Sprite(shader, texture, glm::vec3(1.0f), *transform, transform);

	AddComponent(collider);
	AddComponent(sprite);

	collider->SetParent(transform);
	sprite->SetParent(transform);
}
Player::~Player() {}

void Player::Start() {}
void Player::Update(float deltaTime) {
	auto inputMgr = InputManager::GetInstance();

	// TODO: Change this to velocity instead of position
	if (inputMgr->IsKeyHeld(GLFW_KEY_A)) {
		GetTransform()->position.x -= mMoveSpeed * deltaTime;
	}
	if (inputMgr->IsKeyHeld(GLFW_KEY_D)) {
		GetTransform()->position.x += mMoveSpeed * deltaTime;
	}	
	if (inputMgr->IsKeyHeld(GLFW_KEY_S)) {
		GetTransform()->position.y -= mMoveSpeed * deltaTime;
	}	
	if (inputMgr->IsKeyHeld(GLFW_KEY_W)) {
		GetTransform()->position.y += mMoveSpeed * deltaTime;
	}

	GameObject::Update(deltaTime);
}