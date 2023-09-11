#include "GameManager.h"

#include <iostream>

#include "Player.h"
#include "Solid.h"

GameManager::GameManager() 
	: mPlayerRef(nullptr) {}

void GameManager::Init(Player* player, std::vector<Solid*> level) {
	mPlayerRef = player;
	mLevel = level;
}

void GameManager::Update(float deltaTime) {
	for (size_t i = 0; i < mLevel.size(); i++) {
		CheckCollisions(mLevel[i]);
	}
}

void GameManager::CheckCollisions(Solid* solid) {
	AABB plColl = mPlayerRef->GetCollider();
	AABB slColl = solid->GetCollider();

	glm::vec3 plPos = plColl.GetPosition();
	glm::vec3 slPos = slColl.GetPosition();

	if (plPos.x < slPos.x + slColl.GetWidth() &&
		plPos.x + plColl.GetWidth() > slPos.x &&
		plPos.y < slPos.y + slColl.GetHeight() &&
		plPos.y + plColl.GetHeight() > slPos.y) {
		std::cout << "Collision happening" << std::endl;
	}
}

GameManager* GameManager::GetInstance() {
	if (!mInstance)
		mInstance = new GameManager();
	return mInstance;
}