#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class Player;
class Solid;

struct Time {
	float elapsed, prev, delta, frameTime;
	float dt = 1 / 60.f;

	Time() : elapsed(0), prev(0), delta(0) {}
	void UpdateTime() {
		elapsed = (float)glfwGetTime();
		frameTime = elapsed - prev;
		prev = elapsed;

		while (frameTime > 0.0f) {
			delta = glm::min(frameTime, dt);
			frameTime -= delta;
		}
	}
};

class GameManager {
private:
	inline static GameManager* mInstance;

	GameManager();

	Player* mPlayerRef;
	std::vector<Solid*> mLevel;

	float mMaxCollisionTestRange = 3500.f;

public:
	Time* GameTime = nullptr;

	void Init(Player* player, std::vector<Solid*> level);

	void Update();

	void CheckCollisions();
	void ResolveCollision(Solid* solid);

	static GameManager* GetInstance();

	Player* GetPlayerRef();

	GameManager(GameManager& other) = delete;
	void operator=(const GameManager&) = delete;
};