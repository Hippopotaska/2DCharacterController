#include "CollisionManager.h"

#include "GameManager.h"
#include <iostream>

#include "Player.h"
#include "Solid.h"

CollisionManager::CollisionManager() {}

void CollisionManager::CheckCollisions(std::vector<Solid*> level) {
	Player* player = GameManager::GetInstance()->GetPlayerRef();
	AABB* plColl = player->GetComponent<AABB>();
	AABB* slColl = nullptr;
	
	glm::vec3 plVel = player->GetVelocity() * GameManager::GetInstance()->GetDeltaTime();

	for (size_t i = 0; i < level.size(); i++)
	{
		slColl = level[i]->GetComponent<AABB>();

		if ((plColl->min.x + plVel.x) < slColl->max.x &&
			(plColl->max.x + plVel.x) > slColl->min.x &&
			(plColl->min.y + plVel.y) < slColl->max.y &&
			(plColl->max.y + plVel.y) > slColl->min.y) {
			ResolveCollision(level[i]);
		}
	}
}

void CollisionManager::ResolveCollision(Solid* solid) {
	Player* player = GameManager::GetInstance()->GetPlayerRef();
	AABB* a = player->GetComponent<AABB>();
	AABB* b = solid->GetComponent<AABB>();

	glm::vec3 plVel = player->GetVelocity() * GameManager::GetInstance()->GetDeltaTime();

	static const glm::vec2 faces[4] = {
		glm::vec2(-1.0f, 0.0f), glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, -1.0f), glm::vec2(0.0f, 1.0f),
	};
	float distances[4] = {
		((a->max.x + plVel.x) - b->min.x),
		(b->max.x - (a->min.x + plVel.x)),
		((a->max.y + plVel.y) - b->min.y),
		(b->max.y - (a->min.y + plVel.y)),
	};

	float intersection = FLT_MAX;
	glm::vec2 bestAxis = glm::vec2(0.0f);

	for (int i = 0; i < 4; i++) {
		if (distances[i] < intersection) {
			intersection = distances[i];
			bestAxis = faces[i];
		}
	}

	CollisionInfo info = CollisionInfo(bestAxis, intersection);
	player->OnCollide(info);
}

CollisionManager* CollisionManager::GetInstance() {
	if (!mInstance)
		mInstance = new CollisionManager();
	return mInstance;
}