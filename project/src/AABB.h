#pragma once

#include "Component.h"

class AABB : public Component {
private:
	glm::vec2 mSize;

public:
	glm::vec2 min = glm::vec2(0.0f);
	glm::vec2 max = glm::vec2(0.0f);

	AABB();
	AABB(Transform nTransform, Transform* nParent, glm::vec2 nSize);
	~AABB();

	void Update(float deltaTime) override;
	
	float GetWidth();
	float GetHeight();
};

struct CollisionInfo {
	glm::vec2 normal = glm::vec2(0.0f);
	float intersectionDepth = 0.0f;
	AABB collidedObject;

	CollisionInfo(glm::vec2 newNormal, float newIntDepth, AABB newColObject) {
		normal = newNormal;
		intersectionDepth = newIntDepth;
		collidedObject = newColObject;
	}
};