#pragma once

#include "Component.h"

class AABB : public Component {
private:
	glm::vec2 mSize;

public:
	glm::vec2 min;
	glm::vec2 max;

	AABB(Transform nTransform, Transform* nParent, glm::vec2 nSize);
	~AABB();

	void Update(float deltaTime) override;
	
	float GetWidth();
	float GetHeight();
};