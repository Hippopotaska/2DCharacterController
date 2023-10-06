#include "GameManager.h"

#include <iostream>

#include "Renderer.h"

#include "Player.h"
#include "Solid.h"

#include "AABB.h"

GameManager::GameManager() 
	: mPlayerRef(nullptr) {}

void GameManager::Init(Player* player, std::vector<Solid*> level) {
	GameTime = new Time();
	
	mPlayerRef = player;
	mLevel = level;
}

void GameManager::Update() {
	GameTime->UpdateTime();
	mPlayerRef->Update(GameTime->delta);
	for (size_t i = 0; i < mLevel.size(); i++)
		mLevel[i]->Update(GameTime->delta);
	CheckCollisions();
	mPlayerRef->LateUpdate(GameTime->delta);

	Renderer::GetInstance()->MoveCamera(*mPlayerRef->transform->GetPosition());
}

#pragma region Collision
// TODO: Do collision checks for the next movement step and make changes to them according to that
// Should prolly make changes to the velocity vectors
void GameManager::CheckCollisions() {
	AABB* plColl = mPlayerRef->GetComponent<AABB>();
	AABB* slColl = nullptr;

	glm::vec3 plVel = mPlayerRef->GetVelocity();

	for (size_t i = 0; i < mLevel.size(); i++)
	{
		slColl = mLevel[i]->GetComponent<AABB>();
		if ((plColl->min.x + plVel.x) < slColl->max.x &&
			(plColl->max.x + plVel.x) > slColl->min.x &&
			(plColl->min.y + plVel.y) < slColl->max.y &&
			(plColl->max.y + plVel.y) > slColl->min.y) {
			ResolveCollision(mLevel[i]);
		}
	}
}
void GameManager::ResolveCollision(Solid* solid) {
	AABB* a = mPlayerRef->GetComponent<AABB>();
	AABB* b = solid->GetComponent<AABB>();

	glm::vec3 plVel = mPlayerRef->GetVelocity();
	
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

	CollisionInfo info = CollisionInfo(bestAxis, intersection, *b);
	mPlayerRef->OnCollide(info);
}
#pragma endregion

GameManager* GameManager::GetInstance() {
	if (!mInstance)
		mInstance = new GameManager();
	return mInstance;
}
Player* GameManager::GetPlayerRef() {
	return mPlayerRef;
}