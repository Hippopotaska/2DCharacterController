#pragma once
#include <list>

// Constructor should probably have some general information we would like to tweak before hand, like window creation etc.
// Other stuff could be always the same, like the player, environment, manager scripts etc.

class Player;
class Solid;

class Game {
private:
	Player* mPlayerRef;
	std::list<Solid*> mLevel[];

	void DoCollision();
public:
	Game();
	~Game();
};