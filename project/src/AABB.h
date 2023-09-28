#pragma once

#include "Component.h"

struct CollisionInfo {
	glm::vec2 position;
	glm::vec2 normal;

	CollisionInfo(glm::vec2 newPosition, glm::vec2 newNormal) {
		position = newPosition;
		normal = newNormal;
	}
};

class AABB : public Component {
private:
	glm::vec2 mSize;

public:
	glm::vec2 min = glm::vec2(0.0f);
	glm::vec2 max = glm::vec2(0.0f);

	AABB(Transform nTransform, Transform* nParent, glm::vec2 nSize);
	~AABB();

	void Update(float deltaTime) override;
	
	float GetWidth();
	float GetHeight();
};