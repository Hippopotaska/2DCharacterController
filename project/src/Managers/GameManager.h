#pragma once

#include <vector>

class Player;
class Solid;

class GameManager {
private:
	inline static GameManager* mInstance;

	GameManager();

	Player* mPlayerRef;
	std::vector<Solid*> mLevel;

public:
	void Init(Player* player, std::vector<Solid*> level);

	void Update(float deltaTime);

	void CheckCollisions();
	void ResolveCollision(Solid* solid);

	static GameManager* GetInstance();

	GameManager(GameManager& other) = delete;
	void operator=(const GameManager&) = delete;
};