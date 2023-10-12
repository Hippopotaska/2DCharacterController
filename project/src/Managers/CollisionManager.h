#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "AABB.h"

class Solid;
class Player;

class CollisionManager {
private:
	inline static CollisionManager* mInstance;

	CollisionManager();

public:
	void CheckCollisions(std::vector<Solid*> level);
	void ResolveCollision(Solid* solid);

	static CollisionManager* GetInstance();

	CollisionManager(CollisionManager& other) = delete;
	void operator=(const CollisionManager&) = delete;
};

struct CollisionInfo {
	glm::vec2 normal = glm::vec2(0.0f);
	float intersectionDepth = 0.0f;

	CollisionInfo(glm::vec2 newNormal, float newIntDepth) {
		normal = newNormal;
		intersectionDepth = newIntDepth;
	}
};