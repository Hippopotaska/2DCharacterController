#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

class Player;
class Solid;

struct Time {
	float elapsed, prev, delta;

	Time() : elapsed(0), prev(0), delta(0) {}
	void UpdateTime() {
		elapsed = (float)glfwGetTime();
		delta = elapsed - prev;
		prev = elapsed;
	}
};

class GameManager {
private:
	inline static GameManager* mInstance;

	GameManager();

	Player* mPlayerRef;
	std::vector<Solid*> mLevel;

public:
	Time* GameTime = nullptr;

	void Init(Player* player, std::vector<Solid*> level);

	void Update();

	void CheckCollisions();
	void ResolveCollision(Solid* solid);

	static GameManager* GetInstance();

	GameManager(GameManager& other) = delete;
	void operator=(const GameManager&) = delete;
};