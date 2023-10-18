#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class CollisionManager;
class Player;
class Solid;

class GameManager {
private:
	inline static GameManager* mInstance;

	Player* mPlayerRef;
	std::vector<Solid*> mLevel;

	CollisionManager* collisionMngr;

	float mMaxCollisionTestRange = 3500.f;
	float mDeltaTime = 0.0f;

	GameManager();

	std::vector<Solid*> LoadLevel();

public:
	static constexpr float GAME_SCALE = 100.f;

	void Init();

	void Update(float deltaTime);

	static GameManager* GetInstance();

	Player* GetPlayerRef();
	inline float GetDeltaTime() { return mDeltaTime; }

	GameManager(GameManager& other) = delete;
	void operator=(const GameManager&) = delete;
};