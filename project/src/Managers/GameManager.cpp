#include "GameManager.h"

#include <iostream>

#include "Player.h"
#include "Solid.h"

#include "AABB.h"

GameManager::GameManager() 
	: mPlayerRef(nullptr) {}

void GameManager::Init(Player* player, std::vector<Solid*> level) {
	mPlayerRef = player;
	mLevel = level;
}

void GameManager::Update(float deltaTime) {
	CheckCollisions();

	mPlayerRef->Update(deltaTime);
	for (size_t i = 0; i < mLevel.size(); i++)
		mLevel[i]->Update(deltaTime);
}

// https://gamedev.stackexchange.com/questions/12875/how-do-i-determine-the-collision-normal-in-an-axis-aligned-bounding-box-collisio Simple explanation
// https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/ Could think about implementing this?
// https://github.com/Hippopotaska/CharacterController/blob/main/Assets/Resources/Scripts/CharacterController.cs
// https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution
void GameManager::CheckCollisions() {
	AABB* plColl = mPlayerRef->GetComponent<AABB>();
	AABB* slColl = nullptr;
	
	glm::vec3 plPos = *plColl->transform.GetPosition();
	glm::vec3 slPos = glm::vec3(0.0f);

	for (size_t i = 0; i < mLevel.size(); i++)
	{
		slColl = mLevel[i]->GetComponent<AABB>();
		slPos = *mLevel[i]->transform->GetPosition();
		if (plPos.x < slPos.x + slColl->GetWidth() &&
			plPos.x + plColl->GetWidth() > slPos.x &&
			plPos.y < slPos.y + slColl->GetHeight() &&
			plPos.y + plColl->GetHeight() > slPos.y) {
			ResolveCollision(mLevel[i]);
		}
	}
}
void GameManager::ResolveCollision(Solid* solid) {
	AABB* a = mPlayerRef->GetComponent<AABB>();
	AABB* b = solid->GetComponent<AABB>();
	
	static const glm::vec2 faces[4] = {
		glm::vec2(-1.0f, 0.0f), glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, -1.0f), glm::vec2(0.0f, 1.0f),
	};
	float distances[4] = {
		(a->max.x - b->min.x),
		(b->max.x - a->min.x),
		(a->max.y - b->min.y),
		(b->max.y - a->min.y),
	};
	
	float intersection = FLT_MAX;
	glm::vec2 bestAxis = glm::vec2(0.0f);

	// Loop through all sides and find the best to use as normal
	for (int i = 0; i < 4; i++) {
		if (distances[i] < intersection) {
			intersection = distances[i];
			bestAxis = faces[i];
		}
	}

	// bestAxis == Normal of the collision
	// Now test moving the player out of the 
	std::cout << "Collision Normal [" << bestAxis.x << ", " << bestAxis.y << "]" << std::endl;

	glm::vec3 fixDir = glm::vec3(bestAxis.x, bestAxis.y, 0.0f);
	glm::vec3 colFix = *mPlayerRef->transform->GetPosition() + (fixDir * 5.0f);
	mPlayerRef->transform->SetPosition(colFix);

	// Move player with the normal
	
}

GameManager* GameManager::GetInstance() {
	if (!mInstance)
		mInstance = new GameManager();
	return mInstance;
}