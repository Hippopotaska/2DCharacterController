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

	for (size_t i = 0; i < mLevel.size(); i++)
	{
		slColl = mLevel[i]->GetComponent<AABB>();
		if (plColl->min.x < slColl->max.x &&
			plColl->max.x > slColl->min.x &&
			plColl->min.y < slColl->max.y &&
			plColl->max.y > slColl->min.y) {
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

	for (int i = 0; i < 4; i++) {
		if (distances[i] < intersection) {
			intersection = distances[i];
			bestAxis = faces[i];
		}
	}
	// TODO: Super jank, doesn't factor in the fact that player might not be a 1:1 box
	glm::vec2 colPos = glm::vec2(a->transform.GetPosition()->x, a->transform.GetPosition()->y) + ((bestAxis * -1.0f) * (a->GetWidth() * 0.5f));
	CollisionInfo info = CollisionInfo(colPos, bestAxis);
	mPlayerRef->OnCollide(info);
}

GameManager* GameManager::GetInstance() {
	if (!mInstance)
		mInstance = new GameManager();
	return mInstance;
}