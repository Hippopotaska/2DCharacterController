#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class Player;
class Solid;

class GameManager {
private:
	inline static GameManager* mInstance;

	GameManager();

	Player* mPlayerRef;
	std::vector<Solid*> mLevel;

	float mMaxCollisionTestRange = 3500.f;
	float mDeltaTime = 0.0f;
public:

	// Compile time sorcery (sets GAME_SCALE to be 100.f (not getter, I swear))
	// Explain this to the user; One unit is equal to 100 => 4 = 400
	static constexpr float GAME_SCALE = 100.f;

	void Init(Player* player, std::vector<Solid*> level);

	void Update(float deltaTime);

	void CheckCollisions();
	void ResolveCollision(Solid* solid);

	static GameManager* GetInstance();

	Player* GetPlayerRef();
	inline float GetDeltaTime() { return mDeltaTime; }

	GameManager(GameManager& other) = delete;
	void operator=(const GameManager&) = delete;
};