#include "GameManager.h"

#include <iostream>
#include <fstream>
#include <string>

#include "Renderer.h"
#include "CollisionManager.h"

#include "Player.h"
#include "Solid.h"

#include "AABB.h"

GameManager::GameManager() 
	: mPlayerRef(nullptr) {}

void GameManager::Init() {
	collisionMngr = collisionMngr->GetInstance();

	mPlayerRef = new Player(glm::vec3(0.f));
	mLevel = LoadLevel();
}

void GameManager::Update(float deltaTime) {
	mDeltaTime = deltaTime;

	mPlayerRef->Update(deltaTime);
	for (size_t i = 0; i < mLevel.size(); i++) {
		mLevel[i]->Update(deltaTime);
	}

	collisionMngr->CheckCollisions(mLevel);
	mPlayerRef->LateUpdate(deltaTime);

	Renderer::GetInstance()->MoveCamera(*mPlayerRef->transform->GetPosition());
}

std::vector<Solid*> GameManager::LoadLevel() {
	// Read config file and then parse data
	std::vector<Solid*> level;

	std::fstream levelConfig;
	std::string dataLine;
	std::vector<float> solidData;

	levelConfig.open("res/levelConfig.txt");
	if (levelConfig.is_open()) {
		while (std::getline(levelConfig, dataLine, ',')) {
			solidData.push_back(std::stoi(dataLine));
			if (solidData.size() == 4) {
				level.push_back(new Solid(glm::vec3(solidData[0], solidData[1], 0.f)
					, glm::vec3(solidData[2] / GAME_SCALE, solidData[3] / GAME_SCALE, 1.f)));
				solidData.clear();
			}
		}
	}
	else {
		std::cout << "Trouble opening level config!" << std::endl;
		return level;
	}
	return level;
}

GameManager* GameManager::GetInstance() {
	if (!mInstance)
		mInstance = new GameManager();
	return mInstance;
}
Player* GameManager::GetPlayerRef() {
	return mPlayerRef;
}