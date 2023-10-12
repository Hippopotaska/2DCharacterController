#pragma once

#include "Component.h"

class AABB : public Component {
private:
	glm::vec2 mSize;
	bool mStatic;

public:
	glm::vec2 min = glm::vec2(0.0f);
	glm::vec2 max = glm::vec2(0.0f);

	AABB();
	AABB(Transform nTransform, Transform* nParent, glm::vec2 nSize, bool isStatic);
	~AABB();

	void Update(float deltaTime) override;
};