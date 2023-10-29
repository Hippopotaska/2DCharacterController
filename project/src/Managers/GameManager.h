#pragma once

#include <vector>

#include "InputManager.h"
#include "CollisionManager.h"
#include "UIManager.h"

class Player;
class Solid;

class GameManager {
private:
	inline static GameManager* mInstance;

	Player* mPlayerRef;
	std::vector<Solid*> mLevel;

	CollisionManager* collisionMngr;

	float mMaxCollisionTestRange = 3500.f;

	float mLastFrameTime = 0.f;
	float mTime = 0.f;
	float mDeltaTime = 0.f;

	GameManager();

	std::vector<Solid*> LoadLevel();

public:
	static constexpr float GAME_SCALE = 100.f;

	void Init();

	void Update();

	static GameManager* GetInstance();

	Player* GetPlayerRef();
	inline float GetDeltaTime() { return mDeltaTime; }

	GameManager(GameManager& other) = delete;
	void operator=(const GameManager&) = delete;
};